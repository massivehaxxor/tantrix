#include <unistd.h>
#include <locale.h>
#include <curses.h>
#include <pthread.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>

#include "logic.h"

#define ROW   20
#define COL   10

#define WIN_H   ROW+2
#define WIN_W   COL+2

const char *logo = " _____ _____ _____ ____  ___ ____  \n"
                   "|_   _| ____|_   _|  _ \\|_ _/ ___| \n"
                   "  | | |  _|   | | | |_) || |\\___ \\ \n"
                   "  | | | |___  | | |  _ < | | ___) |\n"
                   "  |_| |_____| |_| |_| \\_\\___|____/ \n";

struct {
  int x, y, w, h;
  int level, score, lines;
  int next_block;

} Score_box = {
  .x = 3,
  .y = 6,
  .w = 14,
  .h = 11,
  .level = 1,
  .next_block = T
};

WINDOW *win_cell;
WINDOW *win_score;

struct Logic *logic;

pthread_t tlogic;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int *cell_old;

int quit;
int is_paused;
int has_color;

int is_unicode = 1;

void new_game();

void curses_quit()
{
  erase();
  endwin();
  exit(0);
}

int display_menu(const char menu_items[][25], int num, int def_item)
{
  int n, i, item = def_item;

  clear();
  refresh();
  addstr(logo);
  do {

    for (i = 0; i < num; i++) {
      if (i == item)
        attron(A_REVERSE);
      mvaddstr(6+(i*1), WIN_W/2, menu_items[i]);
      attroff(A_REVERSE);
    }

    n = getch();

    switch (n) {
      case KEY_DOWN: item++; if (item > (num-1)) item = 0; break;
      case KEY_UP:   item--; if (item < 0) item = num-1; break;
    }
    
    refresh();
  } while (n != '\n');

  return item;
}

void display_unicode_menu()
{
  const char menu[2][25] = {
    "ASCII",
    "UNICODE",
  };

  is_unicode = display_menu(menu, 2, is_unicode);
}

void display_main_menu()
{
  int item = -1;

  const char menu[3][25] = {
    "New Game",
    "Options",
    "Quit",
  };

  while (1) {
    switch (item = display_menu(menu, 3, 0)) {
      case 0:
        new_game();
        break;
      case 1:
        display_unicode_menu();
        break;
      case 2:
        curses_quit();
        break;
      default:
        break;
    }
  }
}

char *box_id_unicode(int id)
{
  if (!id)
    return " ";

  switch (id) {
    case T: return "\u25a9";
    case Z: return "\u25a8"; 
    case L: return "\u25a7"; 
    case RL: return "\u25a6";
    case S: return "\u25a5";
    case I: return "\u25a4";
    case RZ: return "\u25a3";
  }
}

void draw_nextblock(struct Logic *logic)
{
  int i, j;

  int x = 1;
  int y = 6;

  for (i = 0; i < NMATRIX; i++)
    for (j = 0; j < NMATRIX; j++) {
      int c = Block_Matrix[logic->next_block->id][UP][i][j];

      if (has_color) wattrset(win_score, COLOR_PAIR(logic->next_block->id+1));
      if (is_unicode)
        mvwaddstr(win_score, y+i, x+j, box_id_unicode(c)); 
      else
        mvwaddch(win_score, y+i, x+j, c ? c + '0' : ' '); 
      if (has_color) wattrset(win_score, COLOR_PAIR(9));
    }
}


void print_cells(int *cells, struct Logic *logic)
{
  int j, i;

  for (i = 0; i < ROW; i++) {
    for (j = 0; j < COL; j++) {
      int c = cells[(i*COL)+j];
      int co = cell_old[(i*COL)+j];

      if (c != co) {
        if (has_color) wattrset(win_cell, COLOR_PAIR(c));

        if (is_unicode)
          mvwaddstr(win_cell, i+1, j+1, box_id_unicode(c)); 
        else
          mvwaddch(win_cell, i+1, j+1, c ? c + '0' : ' '); 
        if (has_color) wattrset(win_cell, COLOR_PAIR(9));
      }
    }
  }

  if (logic->level != Score_box.level) {
    Score_box.level = logic->level;
    mvwprintw(win_score, 1, 1, "LEVEL: %d", Score_box.level);
  }
  if (logic->score != Score_box.score) {
    Score_box.score = logic->score;
    mvwprintw(win_score, 2, 1, "SCORE: %d", Score_box.score);
  }
  if (logic->lines != Score_box.lines) {
    Score_box.lines = logic->lines;
    mvwprintw(win_score, 3, 1, "LINES: %d", Score_box.lines);
  }
  if (Score_box.next_block != logic->next_block->id) {
    Score_box.next_block = logic->next_block->id;
    draw_nextblock(logic);
  }

  wrefresh(win_score);
  wrefresh(win_cell);
}


void gameover()
{
  int cells[ROW*COL];
  WINDOW *win_gameover;

  win_gameover = newwin(3, 20, Score_box.y, Score_box.x+Score_box.w+3+WIN_W+3);
  box(win_gameover, '|', '=');
  if (has_color) wattrset(win_gameover, COLOR_PAIR(6));
  mvwaddstr(win_gameover, 1, 6, "Game Over");
  if (has_color) wattrset(win_gameover, COLOR_PAIR(1));
  wrefresh(win_gameover);

  getch();
  delwin(win_gameover);
}

void *tlogic_func(void *arg)
{
  struct Logic *logic = (struct Logic *) arg;
  while (1) {
    int cells[ROW*COL];

    if (is_paused)
      goto SKIP;

    if (logic->isOver)
      pthread_exit(0);

    pthread_mutex_lock(&mutex); /* Shared data access */
    Logic_advance(logic, DOWN);
    Logic_get_cell(logic, cells);
    print_cells(cells, logic);
    pthread_mutex_unlock(&mutex);
    if (logic->isOver)
      gameover();
    memcpy(cell_old, cells, sizeof(int) * ROW * COL);
SKIP:
    usleep(1000000 - (logic->level * 100000 ) );
  }
  return NULL;
}

void draw_overlay()
{
  mvwprintw(win_score, 1, 1, "LEVEL: %d", Score_box.level);
  mvwprintw(win_score, 2, 1, "SCORE: %d", Score_box.score);
  mvwprintw(win_score, 3, 1, "LINES: %d", Score_box.lines);
  mvwaddstr(win_score, 4, 1, "NEXT:");

  mvaddstr(Score_box.y+Score_box.h+1, Score_box.x+1, "- Use arrow");
  mvaddstr(Score_box.y+Score_box.h+2, Score_box.x+1, "keys & Space.");
  mvaddstr(Score_box.y+Score_box.h+4, Score_box.x+1, "- Press 'q'");
  mvaddstr(Score_box.y+Score_box.h+5, Score_box.x+1, "to exit game.");
  mvaddstr(Score_box.y+Score_box.h+7, Score_box.x+1, "- Press 'p'");
  mvaddstr(Score_box.y+Score_box.h+8, Score_box.x+1, "to pause game.");
}

void draw_screen()
{
  clear();
  if (has_color) attrset(COLOR_PAIR(1));
  addstr(logo);
  if (has_color) attrset(COLOR_PAIR(9));
  box(win_score, '|', '=');
  draw_overlay();
  draw_nextblock(logic);
  box(win_cell, '|', '=');
  refresh();
  wrefresh(win_cell);
}


void init_colors()
{
  init_pair(1, COLOR_YELLOW, COLOR_BLACK);
  init_pair(2, COLOR_YELLOW, COLOR_BLACK);
  init_pair(3, COLOR_CYAN, COLOR_BLACK);
  init_pair(4, COLOR_BLUE, COLOR_BLACK);
  init_pair(5, COLOR_GREEN, COLOR_BLACK);
  init_pair(6, COLOR_RED, COLOR_BLACK);
  init_pair(7, COLOR_MAGENTA, COLOR_BLACK);
  init_pair(8, COLOR_WHITE, COLOR_BLACK);
  init_pair(9, COLOR_WHITE, COLOR_BLACK);
}

void resize(int sig)
{
  int nh, nw;
  getmaxyx(stdscr, nh, nw);

  if (nw < (WIN_W + Score_box.w + Score_box.x) || nh < (WIN_H + Score_box.y)) {
    fprintf(stderr, "I need more space for drawing. Bye.\n");
    quit = 1;
  }
  draw_screen();
}

void curses_init()
{
  initscr();
  noecho();
  curs_set(0);
  keypad(stdscr, TRUE);
  has_color = has_colors();
  start_color();
  if (has_color) init_colors();
  signal(SIGWINCH, resize);
  //cbreak();
}

void new_game()
{
  win_cell = newwin(WIN_H, WIN_W, Score_box.y, Score_box.x+Score_box.w+3);
  assert(win_cell);

  win_score = newwin(Score_box.h, Score_box.w, Score_box.y, Score_box.x);
  assert(win_cell);

  logic = Logic_init(ROW, COL);

  draw_screen();

  cell_old = malloc(sizeof(int) * ROW * COL);

  pthread_create(&tlogic, NULL, tlogic_func, (void *) logic);

  while (!logic->isOver) {
    int n = getch();
    int cells[ROW*COL];

    if (n == 'p')
      is_paused = !is_paused;

    if (is_paused)
      continue;

    pthread_mutex_lock(&mutex); /* Shared data access */
    switch (n) {
      case 'q':
        logic->isOver = 1;
        break;
      case KEY_UP: //up
        Block_rotate(logic, logic->cur_block); 
        break;
      case KEY_DOWN: //down
        Logic_advance(logic, DOWN);
        break;
      case KEY_RIGHT: //right
        Logic_advance(logic, RIGHT);
        break;
      case KEY_LEFT: //left
        Logic_advance(logic, LEFT);
        break;
      case ' ': //space
        Block_hard_drop(logic);
        if (logic->isOver) {
          Logic_get_cell(logic, cells);
          print_cells(cells, logic);
          gameover();
          goto GAME_EXIT;
        }
        break;
    }
    Logic_get_cell(logic, cells);
    print_cells(cells, logic);
    pthread_mutex_unlock(&mutex);
    memcpy(cell_old, cells, sizeof(int) * ROW * COL);
  }

GAME_EXIT:
  delwin(win_cell);
  delwin(win_score);
  Logic_quit(logic);
  pthread_cancel(tlogic);
  pthread_join(tlogic, NULL);
  free(cell_old);
}

int main(int argc, char *argv[])
{
  setlocale(LC_ALL, "");
  curses_init();

  display_main_menu();

  curses_quit();

  return 0;
}

