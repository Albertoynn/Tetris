#ifndef CONTEXT_H
#define CONTEXT_H

typedef struct board board;
typedef struct piece piece;

typedef unsigned int GLenum;

// clear screen, reset the perspective matrix, and some other stuff
void context_clear();

// render a cuve on specific location @color is linked with the piece value
void context_drawcube(char color, float x, float y, float scale);

// draw a quad in front of the camera
void context_image();

// draw a cube with quads, send vertices and uv mapping
void context_cube();

// render each matrix data of the board as a cube if != ' ' or '\0'
void render_board(board *);

// render each matrix data of the piece as a cube if != ' ' or '\0'
void render_piece(piece *, float x, float y);

// render 4 line of cube to highlight the limit of the board
void render_box(board *);

// used to check if somethink is going wrong on the rendering
const char *GLErrorString(GLenum error);

#endif
