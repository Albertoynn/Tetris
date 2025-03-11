#include <GL/gl.h>

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

#include "board.h"
#include "context.h"
#include "game.h"
#include "texture.h"
#include "window.h"

#include "test/board.h"

#define width  300
#define height 300

pid_t pid;

void close_fork()
{
    kill(pid, SIGKILL);
}

void doGraphic()
{
    srand(time(0));
    atexit(close_fork);
    pid = fork();

    if(pid == 0)
    {
        while(true)
        {
            execlp("mpg123", "/usr/bin/mpg123", "sound.mp3", NULL);
            // do not overflow if mpg123 is not found
            sleep(1);
        }
    }

    void *window = window_new(width, height);
    game *g = 0;

    glViewport(0, 0, width, height);

    event ev;
    ev.eventype = -1;
    ev.key = 0;

    struct timeval time;
    gettimeofday(&time, NULL);
    long last = (time.tv_sec * 1000) + (time.tv_usec / 1000);
    long timestamp = 1000;

    image *s = texture_load("start.bmp");
    GLuint start = texture_upload(s);
    texture_free(s);

    image *t = texture_load("texture.bmp");
    GLuint texture = texture_upload(t);
    texture_free(t);

    GLuint mesh = glGenLists(1);

    // escape == 27
    while(ev.eventype != e_evt_keyboard || ev.key != 27)
    {
        if(!g)
        {
            context_clear();
            glBindTexture(GL_TEXTURE_2D, start);
            context_image();

            if((ev = wait_event(window)).eventype == e_evt_keyboard)
            {
                g = game_new(rand() % 7, 20, 30);
                g->next = piece_new(rand() % 7);
                glNewList(mesh, GL_COMPILE);
                render_board(g->b);
                render_box(g->b);
                glEndList();
                continue;
            }
        }
        else
        {
            gettimeofday(&time, NULL);
            long current = (time.tv_sec * 1000) + (time.tv_usec / 1000);

            if((current - last) > timestamp)
            {
                last = current;
                // build fake keyboard event
                ev.eventype = e_evt_keyboard;
                ev.key = 's';
            }
            else
                ev = wait_event(window);

            if(ev.eventype == e_evt_keyboard && ev.key != 27)
            {
                switch(game_event(g, ev.key))
                {
                    case 0:
                        // nothink;
                        break;
                    case 1:
                        game_free(g);
                        g = 0;
                        // reset the loop
                        continue;
                        break;
                    case 2:
                        timestamp = 1000 - max(500, 10 * g->line);
                        g->next = piece_new(rand() % 7);
                        glNewList(mesh, GL_COMPILE);
                        render_board(g->b);
                        render_box(g->b);
                        glEndList();
                        break;
                }
            }

            context_clear();
            {
                glBindTexture(GL_TEXTURE_2D, texture);
                glMatrixMode(GL_MODELVIEW);
                if(g->next)
                    render_piece(g->next, -5.f, 15.f);
                render_piece(g->p, g->x, g->y);
                glCallList(mesh);
            }
        }

        window_update(window);
        {
            GLenum g = glGetError();
            if(g != GL_NO_ERROR)
                printf("GL: %s\n", GLErrorString(g));
        }
    }

    game_free(g);
    window_free(window);
}
