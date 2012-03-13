#ifndef __LOGIC_H
#define __LOGIC_H

enum Block_type { T = 1, Z, L, RL, S, I, RZ};

enum Block_pos { UP, LEFT, RIGHT, DOWN };

struct Block {
    int id;
    int pos;
    int x, y;
};

struct Logic {
    int *cells;
    int nrow;
    int ncol;
    struct Block *cur_block;
    struct Block *next_block;
    int level;
    int score;
    int lines;
};

extern struct Logic *Logic_init(int row, int col);
extern int Logic_advance(struct Logic *logic, int dir);
extern void Logic_quit(struct Logic *logic);
extern void Logic_get_cell(const struct Logic *logic, int *cells);
extern void Block_rotate(struct Logic *logic, struct Block *block);
extern void Block_hard_drop(struct Logic *logic);
#endif
