#ifndef _BUTTON_KEYBOARD_
#define _BUTTON_KEYBOARD_

#include <vita2d.h>
#include <psp2/ctrl.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include <psp2/touch.h>

typedef struct {
    char print_name;
    int x;
    int y;
} charKey;

extern charKey keys[];
extern vita2d_pgf *keys_pgf;
extern int cursor;
extern int frame;

extern void init_keyboard();
extern void set_key_chars(int option); //zero for letters, 1 for special chars.
extern char *keyboard_get(int max);
extern void draw_keys(char *text);
extern void keyboard_cleanup();
extern void draw_key(charKey key, bool selected);
#endif
