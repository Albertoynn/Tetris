#include "../board.h"
#include "../game.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void test_all_board()
{
    //  some test about piece function
    printf("piece function test :\n\n");

    {
        int i;
        for(i = 0; i < 7; ++i)
        {
            printf("----------\n");
            printf("> original\n");
            piece *tmp = piece_new(i);
            piece_print(tmp);

            printf("> rotate_left\n");
            piece_rotate_left(tmp);
            piece_print(tmp);

            printf("> rotate_right\n");
            piece_rotate_right(tmp);
            piece_print(tmp);

            piece_free(tmp);
        }
    }

    printf("\n board function test :\n\n");

    //  some test of board function
    {
        piece *c = piece_new(0);
        piece *p = piece_new(6);
        board *tmp = board_new(8, 10);
        board_insert(tmp, c, 3, 2);
        board_insert(tmp, p, 0, 5);
        board_insert(tmp, p, 2, 5);
        board_insert(tmp, p, 4, 5);
        board_insert(tmp, p, 6, 5);
        printf("\n");
        board_print(tmp);
        printf("\n");
        board_erase(tmp, 9);
        board_erase(tmp, 9);
        board_erase(tmp, 9);
        board_print(tmp);
        board_free(tmp);
    }
}
