#ifndef _BUTTON_KEYBOARD_
#define _BUTTON_KEYBOARD_

#include <vita2d.h>
#include <psp2/ctrl.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char print_name;
    int x;
    int y;
} charKey;

extern charKey keys[];
extern vita2d_pgf *pgf;

extern void init_keyboard();
extern char *keyboard_get(int max, int x, int y);
extern void cleanup();
#endif
