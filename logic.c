#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "logic.h"

enum { NBLOCK = 7, NMATRIX = 4, NPOS = 4 };

#define M_CENTER NMATRIX / 2

int Block_Matrix[NBLOCK][NPOS][NMATRIX][NMATRIX] = {
  { // RL
    { // UP
      {0, 0, 1, 0},
      {0, 0, 1, 0},
      {0, 1, 1, 0},
      {0, 0, 0, 0},
    }, 
    { // RIGHT
      {0, 0, 0, 1},
      {0, 1, 1, 1},
      {0, 0, 0, 0},
      {0, 0, 0, 0},
    }, 
    { // DOWN
      {0, 0, 1, 1},
      {0, 0, 1, 0},
      {0, 0, 1, 0},
      {0, 0, 0, 0},
    }, 
    { // LEFT
      {0, 1, 1, 1},
      {0, 0, 0, 1},
      {0, 0, 0, 0},
      {0, 0, 0, 0},
    }, 
  },
  { // L

    { // L_UP
      {0, 0, 1, 0},
      {0, 0, 1, 0},
      {0, 0, 1, 1},
      {0, 0, 0, 0},
    }, 
    { // L_RIGHT
      {0, 1, 1, 1},
      {0, 1, 0, 0},
      {0, 0, 0, 0},
      {0, 0, 0, 0},
    }, 
    { // L_DOWN
      {0, 0, 1, 1},
      {0, 0, 0, 1},
      {0, 0, 0, 1},
      {0, 0, 0, 0},
    }, 
    { // L_LEFT
      {0, 0, 0, 1},
      {0, 1, 1, 1},
      {0, 0, 0, 0},
      {0, 0, 0, 0},
    }, 
  },
  { // T
    { // UP
      {0, 0, 1, 0},
      {0, 1, 1, 1},
      {0, 0, 0, 0},
      {0, 0, 0, 0},
    }, 
    { // RIGHT
      {0, 0, 1, 0},
      {0, 0, 1, 1},
      {0, 0, 1, 0},
      {0, 0, 0, 0},
    }, 
    { // DOWN
      {0, 1, 1, 1},
      {0, 0, 1, 0},
      {0, 0, 0, 0},
      {0, 0, 0, 0},
    }, 
    { // LEFT
      {0, 0, 1, 0},
      {0, 1, 1, 0},
      {0, 0, 1, 0},
      {0, 0, 0, 0},
    }, 
  },

  { // Z
    { // UP
      {0, 0, 1, 1},
      {0, 1, 1, 0},
      {0, 0, 0, 0},
      {0, 0, 0, 0},
    }, 
    { // RIGHT
      {0, 0, 1, 0},
      {0, 0, 1, 1},
      {0, 0, 0, 1},
      {0, 0, 0, 0},
    }, 
    { // DOWN
      {0, 0, 1, 1},
      {0, 1, 1, 0},
      {0, 0, 0, 0},
      {0, 0, 0, 0},
    }, 
    { // LEFT
      {0, 0, 1, 0},
      {0, 0, 1, 1},
      {0, 0, 0, 1},
      {0, 0, 0, 0},
    }, 
  },

  { // RZ
    { // UP
      {0, 1, 1, 0},
      {0, 0, 1, 1},
      {0, 0, 0, 0},
      {0, 0, 0, 0},
    }, 
    { // RIGHT
      {0, 0, 0, 1},
      {0, 0, 1, 1},
      {0, 0, 1, 0},
      {0, 0, 0, 0},
    }, 
    { // DOWN
      {0, 1, 1, 0},
      {0, 0, 1, 1},
      {0, 0, 0, 0},
      {0, 0, 0, 0},
    }, 
    { // LEFT
      {0, 0, 0, 1},
      {0, 0, 1, 1},
      {0, 0, 1, 0},
      {0, 0, 0, 0},
    }, 
  },
  { // S
    { // UP
      {0, 0, 1, 1},
      {0, 0, 1, 1},
      {0, 0, 0, 0},
      {0, 0, 0, 0},
    }, 
    { // RIGHT
      {0, 0, 1, 1},
      {0, 0, 1, 1},
      {0, 0, 0, 0},
      {0, 0, 0, 0},
    }, 
    { // DOWN
      {0, 0, 1, 1},
      {0, 0, 1, 1},
      {0, 0, 0, 0},
      {0, 0, 0, 0},
    }, 
    { // LEFT
      {0, 0, 1, 1},
      {0, 0, 1, 1},
      {0, 0, 0, 0},
      {0, 0, 0, 0},
    }, 
  },

  { // I
    { // UP
      {0, 0, 1, 0},
      {0, 0, 1, 0},
      {0, 0, 1, 0},
      {0, 0, 1, 0},
    }, 
    { // RIGHT
      {0, 0, 0, 0},
      {0, 0, 0, 0},
      {1, 1, 1, 1},
      {0, 0, 0, 0},
    },
    { // DOWN
      {0, 0, 1, 0},
      {0, 0, 1, 0},
      {0, 0, 1, 0},
      {0, 0, 1, 0},
    }, 
    { // LEFT
      {0, 0, 0, 0},
      {0, 0, 0, 0},
      {1, 1, 1, 1},
      {0, 0, 0, 0},
    }, 
  },
};

struct Block *Block_new()
{
  struct Block *block;

  block = malloc(sizeof(struct Block));
  assert(block);

  block->id = rand() % NBLOCK;
  block->pos = UP;
  block->x = COL / 2;
  block->y = M_CENTER;

  return block;
}

int *Cells_new()
{
  int *cells;

  cells = calloc(ROW * COL, sizeof(int));
  assert(cells);
  memset(cells, 0, sizeof(int) * ROW * COL);

  return cells;
}

struct Logic *Logic_init()
{
  struct Logic *logic;
  struct Block *block;

  srand(time(NULL)); 
  logic = malloc(sizeof(struct Logic));
  assert(logic);

  logic->nrow = ROW;
  logic->ncol = COL;

  logic->cells = Cells_new();
  assert(logic->cells);

  block = Block_new();
  logic->cur_block= block;

  block = Block_new();
  logic->next_block = block;

  return logic;
}



/*
 * does_collide: returns 1 if the given block collides or outside borders, 0 otherwise 
 */
int does_collide(struct Logic *logic, struct Block *block)
{
  int j, i;
  int mx = block->x - M_CENTER; /* cell coor. for matrix scan top left */
  int my = block->y - M_CENTER;

  for (j = 0; j < NMATRIX; j++) 
    for (i = 0; i < NMATRIX; i++) {
      int x = mx + i;
      int y = my + j;
      int b = Block_Matrix[block->id][block->pos][j][i];
      int is_out = (x < 0 || x >= COL || y < 0 || y >= ROW);
      if ( b && is_out ) 
        return 1;
      if (is_out)
        continue;
      assert((y*COL+x) >= 0 && (y*COL+x) < ROW * COL);
      if (logic->cells[y*COL+x] && b)
        return 1;
    }

  return 0;
}

/*
 * put_block: puts the block in cell area
 */
void put_block(struct Logic *logic, struct Block *block)
{
  int j, i;
  int mx = block->x - M_CENTER;
  int my = block->y - M_CENTER;

  for (j = 0; j < NMATRIX; j++)
    for (i = 0; i < NMATRIX; i++) {
      int x = mx + i;
      int y = my + j;
      int b = Block_Matrix[block->id][block->pos][j][i]; 
      int is_out = (x < 0 || x >= COL || y < 0 || y >= ROW);
      if (is_out)
        continue;
      assert((y*COL+x) >= 0 && (y*COL+x) < ROW * COL);
      if (logic->cells[y*COL+x] == 0)
        logic->cells[y*COL+x] = b;
    }
}

/*
 * Logic_advance: concludes the periodic step (no user input)
 */
int Logic_advance(struct Logic *logic, int dir)
{
  if (Block_move(logic, logic->cur_block, dir) && dir == DOWN) {
    struct Block *temp;

    if (does_collide(logic, logic->next_block)) {
      printf("GAME OVER\n");
      getchar();
    }
    put_block(logic, logic->cur_block);
    free(logic->cur_block);
    logic->cur_block = logic->next_block;
    temp = Block_new();
    logic->next_block = temp;

    return 1;
  }

  return 0;
}
/*
 * Logic_get_cell: returns a pointer to a disposable 2d array of 
 * cell area
 */
void Logic_get_cell(struct Logic *logic, int *cells)
{
  struct Block *block = logic->cur_block;
  struct Logic tlogic; 

  cells = memcpy(cells, logic->cells, sizeof(int) * ROW * COL);
  memcpy(&tlogic, logic, sizeof(struct Logic)); 
  tlogic.cells = cells;

  put_block(&tlogic, block); /* dirty hackaround to pass the cells array through a temp. Logic struct */
}

/*
 * Block_move: moves the block in the specified direction 
 * returns 1 if doesn't due to collision
 */
int Block_move(struct Logic *logic, struct Block *block, int dir)
{
  switch (dir) {
    case DOWN:
      block->y++;
      if (does_collide(logic, block)) {
        block->y--;
        return 1;
      }
      break;
    case RIGHT:
      block->x++;
      if (does_collide(logic, block)) {
        block->x--;
        return 1;
      }
      break;
    case LEFT:
      block->x--;
      if (does_collide(logic, block)) {
        block->x++;
        return 1;
      }
      break;
  }
  return 0;
}

void Block_rotate(struct Logic *logic, struct Block *block)
{
  block->pos++; if (block->pos > 3) block->pos = 0;
}

void Logic_quit(struct Logic *logic)
{
  free(logic->cur_block);
  free(logic->next_block);
  free(logic->cells);
}

