#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

#include "logic.h"

#define ROW 20
#define COL 10

void print_cells(int *cells, struct Logic *logic)
{
  system("clear");
  int j, i;

  for (i = 0; i < COL+2; i++)
    putchar('#');
  putchar('\n');

  for (i = 0; i < ROW; i++) {
    putchar('#');
    for (j = 0; j < COL; j++) {
      printf("%c", cells[(i*COL)+j] ? cells[(i*COL)+j] + '0' : ' '); 
    }
    putchar('#');
    putchar('\n');
  }

  for (i = 0; i < COL+2; i++)
    putchar('#');
  putchar('\n');

  printf("Press q to exit\n");
  printf("LEVEL: %d\n"
         "SCORE: %d\n"
         "LINES: %d\n",
         logic->level,
         logic->score,
         logic->lines);
}

void *tlogic_func(void *arg)
{
  struct Logic *logic = (struct Logic *) arg;
  while (1) {
    int cells[ROW*COL];

    Logic_advance(logic, DOWN);
    Logic_get_cell(logic, cells);
    print_cells(cells, logic);
    usleep(1000000 - (logic->level * 100000 ) );
  }
}

int main()
{
  struct Logic *logic = Logic_init(ROW, COL);
  pthread_t tlogic;

  pthread_create(&tlogic, NULL, tlogic_func, (void *) logic);

  termios_init();

  while(1) {
    int n = getchar();

    if (n != EOF) {
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
    }

    usleep(1000000 / 30);
  }

  Logic_quit(logic);
  return 0;
}

