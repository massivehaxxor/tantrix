#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

#include "logic.h"


void print_cells(int *cells)
{
  system("clear");
  int j, i;

  for (i = 0; i < COL+2; i++)
    putchar('#');
  putchar('\n');

  for (i = 0; i < ROW; i++) {
    putchar('#');
    for (j = 0; j < COL; j++) {
      printf("%c", cells[(i*COL)+j] ? 'x' : ' '); 
    }
    putchar('#');
    putchar('\n');
  }

  for (i = 0; i < COL+2; i++)
    putchar('#');
  putchar('\n');

  printf("Press q to exit\n");
}

void *tlogic_func(void *arg)
{
  struct Logic *logic = (struct Logic *) arg;
  while (1) {
    int cells[ROW*COL];

    Logic_advance(logic, DOWN);
    Logic_get_cell(logic, cells);
    print_cells(cells);
    sleep(1);
  }
}

int main()
{
  struct Logic *logic = Logic_init();
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
          while (!Logic_advance(logic, DOWN)) {}
          break;
      }
      Logic_get_cell(logic, cells);
      print_cells(cells);
    }

    usleep(1000000 / 30);
  }

  Logic_quit(logic);
  return 0;
}

