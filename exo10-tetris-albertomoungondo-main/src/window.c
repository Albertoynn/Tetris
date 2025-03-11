#include "window.h"

#include <stdio.h>
#include <stdlib.h>

#include <GL/gl.h>
#include <GL/glx.h> /* this includes the necessary X headers */

#include <X11/X.h> /* X11 constant (e.g. TrueColor) */
#include <X11/keysym.h>

#pragma GCC diagnostic ignored "-Wimplicit-fallthrough"

void *fatalError(void *window, const char *message)
{
    fprintf(stderr, "main: %s\n", message);
    free(window);
    return 0;
}

typedef struct window
{
        Window win;
        Display *dpy;
        XVisualInfo *vi;
        Colormap cmap;
        XSetWindowAttributes swa;
        GLXContext cx;
        int dummy;
        GLboolean doubleBuffer;
} window;

static int snglBuf[] = {GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_SAMPLE_BUFFERS, 1, GLX_SAMPLES, 8, None};
static int dblBuf[] = {GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_SAMPLE_BUFFERS, 1, GLX_SAMPLES, 8, GLX_DOUBLEBUFFER, None};

void *window_new(unsigned width, unsigned height)
{
    window *tmp = (window *)malloc(sizeof(window));
    tmp->doubleBuffer = GL_TRUE;

    tmp->dpy = XOpenDisplay(NULL);
    if(!tmp->dpy)
        return fatalError(tmp, "could not open display");

    if(!glXQueryExtension(tmp->dpy, &tmp->dummy, &tmp->dummy))
        return fatalError(tmp, "X server has no OpenGL GLX extension");

    // check if double-buffer is available
    tmp->vi = glXChooseVisual(tmp->dpy, DefaultScreen(tmp->dpy), dblBuf);
    if(!tmp->vi)
    {
        tmp->vi = glXChooseVisual(tmp->dpy, DefaultScreen(tmp->dpy), snglBuf);
        if(!tmp->vi)
            return fatalError(tmp, "no RGB visual with depth buffer");
        tmp->doubleBuffer = GL_FALSE;
    }

    // create opengl context
    tmp->cx = glXCreateContext(tmp->dpy, tmp->vi, None, GL_TRUE);
    if(!tmp->cx)
        return fatalError(tmp, "could not create rendering context");

    /* create an X colormap since probably not using default visual */
    tmp->cmap = XCreateColormap(tmp->dpy, RootWindow(tmp->dpy, tmp->vi->screen), tmp->vi->visual, AllocNone);
    tmp->swa.colormap = tmp->cmap;
    tmp->swa.border_pixel = 0;
    tmp->swa.event_mask = KeyPressMask | ExposureMask | ButtonPressMask | StructureNotifyMask;

    tmp->win = XCreateWindow(tmp->dpy, RootWindow(tmp->dpy, tmp->vi->screen), 0, 0, width, height, 0, tmp->vi->depth, InputOutput, tmp->vi->visual, CWBorderPixel | CWColormap | CWEventMask, &tmp->swa);

    // set title
    XSetStandardProperties(tmp->dpy, tmp->win, "gletrix", "gletrix", None, 0, 0, NULL);

    // link opengl context
    glXMakeCurrent(tmp->dpy, tmp->win, tmp->cx);
    XMapWindow(tmp->dpy, tmp->win);

    return tmp;
}

event wait_event(void *i)
{
    window *win = (window *)i;

    event tmp;
    XEvent event;
    tmp.up = false;
    tmp.eventype = e_evt_noevent;

    // if event append
    if(XPending(win->dpy))
    {
        XNextEvent(win->dpy, &event);
        switch(event.type)
        {
            case KeyRelease:
                tmp.up = true;
            case KeyPress:
            {
                KeySym keysym;
                XLookupString((XKeyEvent *)&event, &tmp.key, 1, &keysym, NULL);
                int xkey = XLookupKeysym(&event.xkey, 0);
                tmp.eventype = e_evt_keyboard;

                // translate keysym to key value (usefull)

                if(xkey == XK_Left)
                    tmp.key = 'q';
                if(xkey == XK_Up)
                    tmp.key = 'e';
                if(xkey == XK_Right)
                    tmp.key = 'd';
                if(xkey == XK_Down)
                    tmp.key = 's';
            }
            break;
            case ButtonRelease:
                tmp.up = true;
            case ButtonPress:
                tmp.mousse = event.xbutton.button;
                tmp.eventype = e_evt_mousse;
                break;
            case ConfigureNotify:
                // reset viewport
                glViewport(0, 0, event.xconfigure.width, event.xconfigure.height);
                tmp.eventype = e_evt_redraw;
            case Expose:
                tmp.eventype = e_evt_redraw;
                break;
        }
    }
    return tmp;
}

void window_update(void *i)
{
    window *win = (window *)i;
    if(!win->doubleBuffer)
        glFlush();
    else
        glXSwapBuffers(win->dpy, win->win);
}

void window_free(void *i)
{
    window *win = (window *)i;
    XDestroyWindow(win->dpy, win->win);
    XCloseDisplay(win->dpy);
    free(win);
}
