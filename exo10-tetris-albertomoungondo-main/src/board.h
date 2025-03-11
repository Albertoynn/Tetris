#ifndef _BOARD_H_
#define _BOARD_H_

#include "tool.h"

typedef struct board
{
        char **data;
        unsigned height;
        unsigned width;
} board;

typedef struct piece
{
        char **data;
        unsigned width;
        unsigned height;
        unsigned form;
} piece;

/*
 * a board is defined by a matrix of character
 * if data[i][j] is diferent to ' ' or '\0'
 * then it's a part of the mesh
 * different value is used for rendering and
 * generated from a piece
 */

// allocate a board, and fill it
board *board_new(unsigned x, unsigned y);

// allocate a new board and copy an existing board (usefull for console game)
board *board_copy(board *);

// add/insert a piece on a board on a specific position {x,y}
void board_insert(board *, piece *, unsigned x, unsigned y);

// check if a piece can be inserted on a board on specific position {x,y}
bool board_intersect(board *, piece *, unsigned x, unsigned y);

// check if a piece at {x,y} is on the board (boundingbox)
bool board_inside(board *, piece *, unsigned x, unsigned y);

// fill the line {y} and pull down each line in {0, y-1}
void board_erase(board *p, unsigned y);

// print on console ...
void board_print(board *);

// remove all line @board_erase if the line is full and return who many line is removed
int board_clear(board *);

// desallocate a board and it's member
void board_free(board *);

/*
 * a piece is defined by a matrix of character
 * if data[i][j] is diferent to ' ' or '\0'
 * then it's a part of the mesh
 * different value is used for rendering
 * a color is calculated in this value for graphic version
 */

// allocate a piece @i is the piece form [0-6]
piece *piece_new(unsigned i);

// allocate a new piece and, copy from an existant piece
piece *piece_copy(piece *);

// rotate a piece on the left (90°)
void piece_rotate_left(piece *);

// rotate a piece on the right (-90°)
void piece_rotate_right(piece *);

// print a piece on console (for testing & debuging)
void piece_print(piece *);

// desallocate a piece and it's member
void piece_free(piece *);

// min between i and j
unsigned min(unsigned i, unsigned j);
// max between i and j
unsigned max(unsigned i, unsigned j);

#endif // _BOARD_H_
