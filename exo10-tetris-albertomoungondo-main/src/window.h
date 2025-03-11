#ifndef WINDOW_H
#define WINDOW_H

#include "tool.h"

enum event_type
{
    e_evt_noevent,
    e_evt_mousse,
    e_evt_keyboard,
    e_evt_redraw
};

typedef struct event
{
        char mousse;
        int eventype;
        char key;
        bool up;
} event;

// open X11 window and link an opengl 1.4 context
void *window_new(unsigned width, unsigned height);

// check if an event is here and return then, otherwise event.eventype is e_evt_noevent
event wait_event(void *window);

// swap opengl double buffer if possible or flush the screen
void window_update(void *window);

// close and free a window
void window_free(void *);

#endif // WINDOW_H
