#ifndef __LOGIC_H
#define __LOGIC_H

enum block_enum_shape { T = 1, Z, L, RL, S, I, RZ};

enum { NBLOCK = 7, NMATRIX = 4, NPOS = 4 };
enum block_enum_pos { UP, LEFT, RIGHT, DOWN };

struct block_t {
    int id;
    int pos;
    int x, y;
};

struct logic_t {
    int *cells;
    int nrow;
    int ncol;
    struct block_t *cur_block;
    struct block_t *next_block;
    int level;
    int score;
    int lines;
    int isOver;
};

extern const int        logic_block_matrix[NBLOCK][NPOS][NMATRIX][NMATRIX];

extern struct logic_t * logic_init (int row, int col);
extern int              logic_advance (struct logic_t *logic, int dir);
extern void             logic_quit (struct logic_t *logic);
extern void             logic_get_cell (const struct logic_t *logic, int *cells);
extern void             logic_block_rotate (struct logic_t *logic, struct block_t *block);
extern void             logic_block_hard_drop (struct logic_t *logic);
#endif
