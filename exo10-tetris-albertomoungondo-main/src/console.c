#include "board.h"
#include "game.h"

#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_t thread;

void updateScreen(game *g)
{
    system("clear");
    printf("line cleared: %d\n", g->line);
    // fake board for console print
    board *tmp = board_copy(g->b);
    board_insert(tmp, g->p, g->x, g->y);
    board_print(tmp);
    board_free(tmp);
}

void doGameEvent(game *g, char c)
{
    pthread_mutex_lock(&mutex);
    switch(game_event(g, c))
    {
        case 0:
            // nothink;
            break;
        case 1:
        {
            exit(0);
        }
        break;
        case 2:
            g->next = piece_new(rand() % 7);
            break;
    }
    updateScreen(g);
    pthread_mutex_unlock(&mutex);
}

void *nextstep(void *p_data)
{
    game *g = (game *)p_data;
    while(true)
    {
        sleep(1);
        doGameEvent(g, 's');
    }
    return 0;
}

void doConsole()
{
    unsigned c;
    srand(time(0));

    game *g = game_new(rand() % 7, 8, 20);
    g->next = piece_new(rand() % 7);
    updateScreen(g);

    // do not wait 'enter' key with getchar
    struct termios ch;
    tcgetattr(STDIN_FILENO, &ch);
    ch.c_lflag &= ~ICANON;
    tcsetattr(STDIN_FILENO, TCSANOW, &ch);

    // thread for time event (1s)
    pthread_create(&thread, NULL, nextstep, (void *)g);

    while(true)
    {
        while((c = getchar()) != 0)
            doGameEvent(g, c);
        usleep(10000);
    }

    game_free(g);
    exit(0);
}
