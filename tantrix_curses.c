
#include <unistd.h>
#include <locale.h>
#include <curses.h>
#include <pthread.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>

#include "logic.h"

#define WIN_H   22
#define WIN_W   12

#define ROW   20
#define COL   10

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

int is_unicode;

void display_unicode_menu()
{
  int n, i, item = 0;

  const char menu[2][25] = {
    "ASCII",
    "UNICODE",
  };

  clear();
  refresh();

  keypad(stdscr, TRUE);

  do {

    for (i = 0; i < 2; i++) {
      if (i == 1)
        attrset(COLOR_PAIR(5));
      if (i == item)
        attron(A_REVERSE);
      mvaddstr(10+(i*1), 10, menu[i]);
      attroff(A_REVERSE);
      attrset(COLOR_PAIR(9));
    }

    n = getch();

    switch (n) {
      case KEY_DOWN: item++; if (item > 1) item = 0; break;
      case KEY_UP:   item--; if (item < 0) item = 1; break;
    }
    
    refresh();
  } while (n != '\n');

  is_unicode = item;

  keypad(stdscr, FALSE);
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

void curses_quit()
{
  erase();
  endwin();
}

void *tlogic_func(void *arg)
{
  struct Logic *logic = (struct Logic *) arg;
  while (1) {
    int cells[ROW*COL];

    if (is_paused)
      goto SKIP;

    pthread_mutex_lock(&mutex);
    Logic_advance(logic, DOWN);
    Logic_get_cell(logic, cells);
    pthread_mutex_unlock(&mutex);

    print_cells(cells, logic);
    if (logic->isOver) {
      curses_quit();
      addstr("GAME OVER\n");
      exit(0);
    }
    memcpy(cell_old, cells, sizeof(int) * ROW * COL);
SKIP:
    usleep(1000000 - (logic->level * 100000 ) );
  }
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

  if (nw < (WIN_W + 10) || nh < (WIN_H + 10)) {
    fprintf(stderr, "I need more space for drawing. Bye.\n");
    exit(0);
  }
  draw_screen();
}

void curses_init()
{
  initscr();
  noecho();
  curs_set(0);

  has_color = has_colors();
  start_color();
  if (has_color) init_colors();

  display_unicode_menu();

  cbreak();


  win_cell = newwin(WIN_H, WIN_W, Score_box.y, Score_box.x+Score_box.w+3);
  assert(win_cell);

  win_score = newwin(Score_box.h, Score_box.w, Score_box.y, Score_box.x);
  assert(win_cell);

  logic = Logic_init(ROW, COL);

  draw_screen();

  signal(SIGWINCH, resize);
}


int main(int argc, char *argv[])
{
  setlocale(LC_ALL, "");
  curses_init();

  cell_old = malloc(sizeof(int) * ROW * COL);

  pthread_create(&tlogic, NULL, tlogic_func, (void *) logic);

  while (!quit) {
    int n = getch();
    int cells[ROW*COL];

    if (n == 'p')
      is_paused = !is_paused;

    if (is_paused)
      continue;

    switch (n) {

      case 113:
        quit = 1;
        break;
      case 65: //up
        Block_rotate(logic, logic->cur_block); 
        break;
      case 66: //down
        Logic_advance(logic, DOWN);
        break;
      case 67: //right
        Logic_advance(logic, RIGHT);
        break;
      case 68: //left
        Logic_advance(logic, LEFT);
        break;
      case 32: //space
        Block_hard_drop(logic);
        if (logic->isOver) {
          curses_quit();
          addstr("GAME OVER\n");
          exit(0);
        }

        break;
    }

    Logic_get_cell(logic, cells);
    print_cells(cells, logic);
    memcpy(cell_old, cells, sizeof(int) * ROW * COL);

  }

  curses_quit();

  return 0;
}

