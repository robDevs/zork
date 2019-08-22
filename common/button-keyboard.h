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
    char *string_name;
    int x;
    int y;
    int w;
    int h;
} charKey;

extern charKey keys[];
extern charKey space, enter, del, next;
extern vita2d_pgf *keys_pgf;
extern int cursor;
extern int frame;

extern unsigned int kb_bg_color, kb_text_color, kb_text_bg_color, kb_text_sel_color, kb_output_color;

extern void kb_set_color(unsigned int *color, int r, int g, int b, int a);

extern bool kb_uppercase;

extern void init_keyboard();
extern void set_key_chars(int option); //zero for letters, 1 for special chars.
extern char *keyboard_get(int max);
extern void draw_keys(char *text);
extern void keyboard_cleanup();
extern void draw_key(charKey key, bool selected);
extern bool check_collision_point_key(charKey key, int x, int y);
#endif
