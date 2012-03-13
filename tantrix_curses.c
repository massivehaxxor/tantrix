#include <ncurses.h>
#include <pthread.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

#include "logic.h"

#define WIN_H   22
#define WIN_W   12

#define ROW   20
#define COL   10

WINDOW *win;

int *cell_old;

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
  wrefresh(win);
}

void *tlogic_func(void *arg)
{
  struct Logic *logic = (struct Logic *) arg;
  while (1) {
    int cells[ROW*COL];

    Logic_advance(logic, DOWN);
    Logic_get_cell(logic, cells);
    print_cells(cells, logic);
    memcpy(cell_old, cells, sizeof(int) * ROW * COL);
    usleep(1000000 - (logic->level * 100000 ) );
  }
}

void curses_init()
{
  initscr();

  win = newwin(WIN_H, WIN_W, 5, 5);
  assert(win);

  box(win, '*', '*');

  refresh();
  wrefresh(win);

  noecho();
  cbreak();
  curs_set(0);
}

void curses_quit()
{
  endwin();
}

int main(int argc, char *argv[])
{
  struct Logic *logic = Logic_init(ROW, COL);
  pthread_t tlogic;

  curses_init();

  cell_old = malloc(sizeof(int) * ROW * COL);

  wclear(win);
  box(win, '*', '*');

  pthread_create(&tlogic, NULL, tlogic_func, (void *) logic);

  while (1) {
    int n = getch();
    int cells[ROW*COL];

    switch (n) {

      case 113:
        exit(0);
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
        break;
    }

    Logic_get_cell(logic, cells);
    print_cells(cells, logic);
    memcpy(cell_old, cells, sizeof(int) * ROW * COL);

  }

  curses_quit();

  return 0;
}

