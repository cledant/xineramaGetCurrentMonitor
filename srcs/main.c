#include <stdio.h>
#include <stdbool.h>

#include <X11/Xlib.h>
#include <X11/extensions/Xinerama.h>

// Defines
#define X_ORG xsi[i].x_org
#define Y_ORG xsi[i].y_org

// Structs
typedef struct s_position
{
    int x;
    int y;
} Position;

// Static functions
static bool
queryMousePosition(Display *dpy, Position *pos)
{
    int win_x;
    int win_y;
    unsigned int mask;
    Window win;
    Window root;

    root = DefaultRootWindow(dpy);
    if (!XQueryPointer(dpy,
                       root,
                       &root,
                       &win,
                       &pos->x,
                       &pos->y,
                       &win_x,
                       &win_y,
                       &mask)) {
        for (int i = -1; i < ScreenCount(dpy); ++i) {
            if (root == RootWindow(dpy, i)) {
                return true;
            }
        }
    }
    return false;
}


int
main(void)
{
    Display *dpy = XOpenDisplay(0);
    if (!dpy) {
        fprintf(stderr, "Failed to open display 0");
        return -1;
    }

    Position mousePosition;
    if (queryMousePosition(dpy, &mousePosition)) {
        fprintf(stderr, "Failed to get mouse position");
        return -1;
    }

    int nbScreen;
    XineramaScreenInfo *xsi = XineramaQueryScreens(dpy, &nbScreen);
    for (int i = 0; i < nbScreen; ++i) {
        const int x_end = X_ORG + xsi[i].width;
        const int y_end = Y_ORG + xsi[i].height;

        if (mousePosition.x >= X_ORG && mousePosition.x < x_end) {
            if (mousePosition.y >= Y_ORG && mousePosition.y < y_end) {
                return xsi[i].screen_number;
            }
        }
    }

    fprintf(stderr, "Mouse outside screens");
    return -1;
}