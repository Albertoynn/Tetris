#ifndef __GAME_HEADER__
#define __GAME_HEADER__

struct board;
struct piece;

typedef struct game
{
        struct board *b;
        struct piece *p;
        struct piece *next;
        unsigned x, y;
        unsigned line;
} game;

// allocate a game, with a fresh board (@b) and a piece(@p)
game *game_new(unsigned piece, unsigned width, unsigned height);

// do all movement and test
// key is:
//   q : left
//   s : down
//   d : right
//   z : right rotation
//   e : left rotation
int game_event(game *, int key);

//
void game_free(game *);

#endif // __GAME_HEADER__
