#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "logic.h"
#include <time.h>

#define M_CENTER NMATRIX / 2

/* static table data for tetromino shapes used for both drawing and collisions;
 * saves a lot of conditional statements for the latter.
 */
const int logic_block_matrix[NBLOCK][NPOS][NMATRIX][NMATRIX] = {
  { // RL
    { // UP
      {0, 0, 1, 0},
      {0, 0, 1, 0},
      {0, 1, 1, 0},
      {0, 0, 0, 0},
    }, 
    { // RIGHT
      {0, 1, 0, 0},
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
      {0, 1, 0, 0},
      {0, 1, 0, 0},
      {0, 1, 1, 0},
      {0, 0, 0, 0},
    }, 
    { // L_RIGHT
      {0, 1, 1, 1},
      {0, 1, 0, 0},
      {0, 0, 0, 0},
      {0, 0, 0, 0},
    }, 
    { // L_DOWN
      {0, 1, 1, 0},
      {0, 0, 1, 0},
      {0, 0, 1, 0},
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

/*
 * Block_new: returns a random block.
 */
static struct block_t *Block_new(const struct logic_t *logic)
{
  struct block_t *block;

  block = malloc(sizeof(struct block_t));
  assert(block);

  block->id = rand() % NBLOCK;
  block->pos = UP;
  block->x = logic->ncol / 2;
  block->y = M_CENTER;

  return block;
}

int *Cells_new(int row, int col)
{
  int *cells;

  cells = calloc(row * col, sizeof(int));
  assert(cells);
  memset(cells, 0, sizeof(int) * row * col); 

  return cells;
}

/*
 * logic_init: returns a struct logic_t upon which all the internal game operations 
 * are to be done.
 * First to be called for a new game.
 */
struct logic_t *logic_init(int row, int col)
{
  struct logic_t *logic;
  struct block_t *block;

  srand(time(NULL)); 
  logic = malloc(sizeof(struct logic_t));
  assert(logic);
  memset(logic, 0, sizeof(struct logic_t));

  logic->nrow = row;
  logic->ncol = col;

  logic->level = 1;

  logic->cells = Cells_new(row, col);
  assert(logic->cells);

  block = Block_new(logic);
  logic->cur_block= block;

  block = Block_new(logic);
  logic->next_block = block;

  return logic;
}

/*
 * does_collide: returns 1 if the given block collides or outside borders, 0 otherwise 
 */
static int does_collide(const struct logic_t *logic, const struct block_t *block)
{
  int j, i;
  int mx = block->x - M_CENTER; /* cell coor. for matrix scan top left */
  int my = block->y - M_CENTER;

  for (j = 0; j < NMATRIX; j++) 
    for (i = 0; i < NMATRIX; i++) {
      int x = mx + i;
      int y = my + j;
      int b = logic_block_matrix[block->id][block->pos][j][i];
      int is_out = (x < 0 || x >= logic->ncol || y < 0 || y >= logic->nrow);
      if ( b && is_out ) 
        return 1;
      if (is_out)
        continue;
      assert((y*logic->ncol+x) >= 0 && (y*logic->ncol+x) < logic->nrow * logic->ncol);
      if (logic->cells[y*logic->ncol+x] && b)
        return 1;
    }
  return 0;
}

/*
 * put_block: places the block in cell area
 */
static void put_block(struct logic_t *logic, const struct block_t *block)
{
  int j, i;
  int mx = block->x - M_CENTER;
  int my = block->y - M_CENTER;

  for (j = 0; j < NMATRIX; j++)
    for (i = 0; i < NMATRIX; i++) {
      int x = mx + i;
      int y = my + j;
      int b = logic_block_matrix[block->id][block->pos][j][i]; 
      int is_out;
      if (!b)
        continue;
      is_out = (x < 0 || x >= logic->ncol || y < 0 || y >= logic->nrow);
      if (is_out)
        continue;
      assert((y*logic->ncol+x) >= 0 && (y*logic->ncol+x) < logic->nrow * logic->ncol);
      if (logic->cells[y*logic->ncol+x] == 0)
        logic->cells[y*logic->ncol+x] = block->id+1;
    }
}

/*
 * clear_lines: clears all the complete lines, scanning the whole cell area,
 * sets score accordingly. returns non-zero if clears, 0 otherwise.
 */
static int clear_lines(struct logic_t *logic)
{
  int i, j;
  int nlines = 0;
  int last_line = 0;

  for (i = 0; i < logic->nrow; i++) {
    int linecount = 0;

    for (j = 0; j < logic->ncol; j++)  {
      if (logic->cells[i*logic->ncol+j])
        linecount++;
    }

    if (linecount == logic->ncol) {
      nlines++;
      last_line = i;
    }
  }
  if (nlines != 0) {
    memmove(&logic->cells[nlines*logic->ncol], logic->cells, sizeof(int) * (last_line-nlines+1) * logic->ncol);
  }

  logic->lines += nlines;
  logic->score += (nlines * 100) * (((double) logic->level / 2) + 1);

  return nlines;
}

/*
 * Block_move: moves the block in the specified direction 
 * returns 1 if doesn't due to collision
 */
static int Block_move(struct logic_t *logic, struct block_t *block, int dir)
{
  switch (dir) {
    case DOWN:  block->y++; if (does_collide(logic, block)) { block->y--; return 1; } break;
    case RIGHT: block->x++; if (does_collide(logic, block)) { block->x--; return 1; } break;
    case LEFT:  block->x--; if (does_collide(logic, block)) { block->x++; return 1; } break;
  }
  return 0;
}

/*
 * logic_advance: concludes the periodic step, returns 1
 * if the block hits, 0 otherwise, 2 if clears a line.
 */
int logic_advance(struct logic_t *logic, int dir)
{
  if (Block_move(logic, logic->cur_block, dir) && dir == DOWN) {
    struct block_t *temp;
    int t;

    put_block(logic, logic->cur_block);

    free(logic->cur_block);
    logic->cur_block = logic->next_block;
    temp = Block_new(logic);
    logic->next_block = temp;

    if (does_collide(logic, logic->cur_block)) {
      logic->isOver = 1;
    }

    t = clear_lines(logic);

    logic->level = (logic->lines / 10) + 1;

    if (t)
      return 2;

    return 1;
  }
  return 0;
}


/*
 * logic_get_cell: returns a pointer to a disposable 2d array of 
 * cell area
 */
void logic_get_cell(const struct logic_t *logic, int *cells)
{
  struct block_t *block = logic->cur_block;
  struct logic_t tlogic; 

  cells = memcpy(cells, logic->cells, sizeof(int) * logic->nrow * logic->ncol);
  memcpy(&tlogic, logic, sizeof(struct logic_t)); 
  tlogic.cells = cells;

  put_block(&tlogic, block); /* dirty hackaround to pass the cells array through a temp. logic_t struct */
}

/*
 * logic_block_rotate: rotates the given block in a fixed direction
 * which is to right.
 */
void logic_block_rotate(struct logic_t *logic, struct block_t *block)
{
  block->pos++; if (block->pos > 3) block->pos = 0;

  if (does_collide(logic, block)) {
    block->pos--; if (block->pos < 0) block->pos = 3;
    return;
  }
}

void logic_block_hard_drop(struct logic_t *logic)
{
  int height = 0;
  int t;

  while ( !(t = logic_advance(logic, DOWN)) )
    height++;

  if (t == 2) /* see logic_advance for 2 */
    logic->score += (height * 5) * ( ((double) logic->level / 2) + 1 );
}

void logic_quit(struct logic_t *logic)
{
  free(logic->cur_block);
  free(logic->next_block);
  free(logic->cells);
  free(logic);
}
