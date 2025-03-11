#include "game.h"
#include "board.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

game *game_new(unsigned piece, unsigned width, unsigned height)
{
    game *g = (game *)malloc(sizeof(game));
    g->b = board_new(width, height);
    g->p = piece_new(piece);
    g->x = g->y = g->line = 0;
    return g;
}

int game_event(game *g, int key)
{
    switch(key)
    {
        case 'z':
            // rotate the piece in left (count-clock)
            // check if the rotated piece hit the board
            // if true restore the previous rotation
            break;
        case 'e':
            // rotate the piece in right (clockwise)
            // check if the rotated piece hit the board
            // if true restore the previous rotation
            // check if the piece is in the board
            break;
        case 'q':
            // move if position at the left can be reached
            break;
        case 'd':
            // move if position at the right can be reached
            break;
        case 's':
        default:
            // if the next movement is not possible
            if(board_intersect(g->b, g->p, g->x, g->y + 1))
            {
                // insert the piece of the current position
                // remove all 'full' line
                // if the next piece hit somethink on the initial position
                if(false)
                {
                    // then loose
                    system("clear");
                    board_insert(g->b, g->p, g->x, g->y);
                    printf("game over oups !\n");
                    printf("removed line : %d\n", g->line);
                    return 1;
                }
                else
                    return 2;
            }
            else
                g->y++;
            break;
    }

    return 0;
}

void game_free(game *g)
{
    board_free(g->b);
    piece_free(g->p);
    free(g);
}
