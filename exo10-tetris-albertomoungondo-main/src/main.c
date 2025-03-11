#include "test/board.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void doConsole();
void doGraphic();

int main(int argc, char **argv)
{
    int opt = -1;

    while((opt = getopt(argc, argv, "htcg")) != -1)
    {
        switch(opt)
        {
            case 'g':
                doGraphic();
                return 0;
                break;
            case 'c':
                doConsole();
                return 0;
                break;
            case 't':
                test_all_board();
                return 0;
                break;
            default:
                printf("help:\n"
                       " -h print this help message\n"
                       " -c play in console\n"
                       " -g play in x11/opengl : (default)\n"
                       " -t some test about piece and board function\n"
                       "------------------\n"
                       "key is: \n"
                       "   q : left\n"
                       "   s : down\n"
                       "   d : right\n"
                       "   z : right rotation\n"
                       "   e : left rotation\n");
                return 0;
                break;
        }
    }

    doGraphic();

    return 0;
}
