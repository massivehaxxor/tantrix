#include <ncurses.h>
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
  .x = 1,
  .y = 6,
  .w = 13,
  .h = 11,
  .level = 1,
  .next_block = T
};

WINDOW *win;

struct Logic *logic;

int *cell_old;

int quit;

void draw_nextblock(struct Logic *logic)
{
  int i, j;

  int x = Score_box.x+1;
  int y = Score_box.y+6;

  for (i = 0; i < NMATRIX; i++)
    for (j = 0; j < NMATRIX; j++) {
      int c = Block_Matrix[logic->next_block->id][UP][i][j];
      mvaddch(y+i, x+j, c ? '#' : ' ');
    }
}

void print_cells(int *cells, struct Logic *logic)
{
  int j, i;

  for (i = 0; i < ROW; i++) {
    for (j = 0; j < COL; j++) {
      int c = cells[(i*COL)+j];
      int co = cell_old[(i*COL)+j];

      if (c != co)
        mvwaddch(win, i+1, j+1, c ? c + '0' : ' '); 
    }
  }

  if (logic->level != Score_box.level) {
    Score_box.level = logic->level;
    mvprintw(Score_box.y+1, Score_box.x+1, "LEVEL: %d", Score_box.level);
  }
  if (logic->score != Score_box.score) {
    Score_box.score = logic->score;
    mvprintw(Score_box.y+2, Score_box.x+1, "SCORE: %d", Score_box.score);
  }
  if (logic->lines != Score_box.lines) {
    Score_box.lines = logic->lines;
    mvprintw(Score_box.y+3, Score_box.x+1, "LINES: %d", Score_box.lines);
  }
  if (Score_box.next_block != logic->next_block->id) {
    Score_box.next_block = logic->next_block->id;
    draw_nextblock(logic);
  }

  wrefresh(win);
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

    Logic_advance(logic, DOWN);
    Logic_get_cell(logic, cells);
    print_cells(cells, logic);
    if (logic->isOver) {
      curses_quit();
      addstr("GAME OVER\n");
      exit(0);
    }
    memcpy(cell_old, cells, sizeof(int) * ROW * COL);
    usleep(1000000 - (logic->level * 100000 ) );
  }
}

void draw_overlay()
{
  mvhline(Score_box.y, Score_box.x+1, '=', Score_box.w-1);
  mvhline(Score_box.y+Score_box.h, Score_box.x+1, '=', Score_box.w-1);
  mvvline(Score_box.y+1, Score_box.x, '|', Score_box.h-1);
  mvvline(Score_box.y+1, Score_box.x+Score_box.w, '|', Score_box.h-1);

  mvprintw(Score_box.y+1, Score_box.x+1, "LEVEL: %d", Score_box.level);
  mvprintw(Score_box.y+2, Score_box.x+1, "SCORE: %d", Score_box.score);
  mvprintw(Score_box.y+3, Score_box.x+1, "LINES: %d", Score_box.lines);
  mvaddstr(Score_box.y+4, Score_box.x+1, "NEXT:");

  mvaddstr(Score_box.y+Score_box.h+1, Score_box.x+1, "- Use arrow");
  mvaddstr(Score_box.y+Score_box.h+2, Score_box.x+1, "keys & Space.");
  mvaddstr(Score_box.y+Score_box.h+4, Score_box.x+1, "- Press 'q'");
  mvaddstr(Score_box.y+Score_box.h+5, Score_box.x+1, "to exit game.");
}

void draw_screen()
{
  clear();
  addstr(logo);
  draw_overlay();
  draw_nextblock(logic);
  box(win, '*', '*');
  refresh();
  wrefresh(win);
}


void resize(int sig)
{
  int nh, nw;
  getmaxyx(stdscr, nh, nw);

  draw_screen();
}

void curses_init()
{
  logic = Logic_init(ROW, COL);
  initscr();

  win = newwin(WIN_H, WIN_W, 6, 16);
  assert(win);

  draw_screen();

  noecho();
  cbreak();
  curs_set(0);

  signal(SIGWINCH, resize);
}


int main(int argc, char *argv[])
{
  pthread_t tlogic;

  curses_init();

  cell_old = malloc(sizeof(int) * ROW * COL);

  pthread_create(&tlogic, NULL, tlogic_func, (void *) logic);

  while (!quit) {
    int n = getch();
    int cells[ROW*COL];

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

