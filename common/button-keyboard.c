#include "button-keyboard.h"
#include "controls.h"

charKey keys[30];
vita2d_pgf *pgf;

void init_keyboard() {
    int count = 0;
    for(char i = 'a'; i <= 'z'; i++) {
        keys[count].print_name = i;
        count++;
    }
    pgf = vita2d_load_default_pgf();
}
char *keyboard_get(int max, int x, int y) {
    reset_keys();
    int done = 0;

    int cursor = 0;
    int text_cursor = 0;

    init_keys();

    char text[100] = "";

    while(done == 0) {
        update_keys();

        if(start_released)
            done = 1;
        if(left_pressed){
            if(cursor == 0 || cursor == 10)
                cursor += 9;
            else if(cursor == 20)
                cursor += 5;
            else
                cursor -= 1;
        }
        if(right_pressed) {
            if(cursor == 9 || cursor == 19)
                cursor -= 9;
            else if(cursor == 25)
                cursor -= 5;
            else
                cursor += 1;
        }
        if(up_pressed) {
            if(cursor <= 9)
                cursor += 20;
            else cursor -= 10;
            if(cursor > 25)
                cursor -= 10;
        }
        if(down_pressed) {
            if(cursor >= 20)
                cursor -= 20;
            else
                cursor += 10;
            if(cursor > 25)
                cursor -= 20;
        }

        if(cross_pressed) {
            if(text_cursor < max) {
                text[text_cursor] = keys[cursor].print_name;
                text_cursor += 1;
                text[text_cursor] = '_';
            }
        }

        if(circle_pressed) {
            if(text_cursor > 0) {
                text[text_cursor] = ' ';
                text_cursor -= 1;
                text[text_cursor] = '_';
            }
            else if(text_cursor == 0)
                text[text_cursor] = '_';
        }
        if(square_pressed) {
            if(text_cursor < max) {
                text[text_cursor] = ' ';
                text_cursor += 1;
                text[text_cursor] = '_';
            }
        }

        vita2d_start_drawing();

        int x_pos = x + 10;
        int y_pos = y - 10;
        int count = 0;

        vita2d_draw_rectangle(x_pos - 10, y_pos-57, 300, 17*3+54, RGBA8(190,190,190,255));

        vita2d_pgf_draw_textf(pgf, x_pos, y_pos - 40, RGBA8(0,0,0,255), 1.0f, ">%s", text);

        for(int i = 0; i <= 30; i++) {
            if(cursor == i)
                vita2d_draw_rectangle(x_pos, y_pos-17, 17, 19, RGBA8(255,255,255,255));
            vita2d_pgf_draw_textf(pgf, x_pos, y_pos, RGBA8(0,0,0,255), 1.0f, "%c", keys[i].print_name);
            x_pos += 30;
            count++;
            if(count >= 10) {
                y_pos += 17;
                x_pos = x + 10;
                count = 0;
            }
        }

        vita2d_end_drawing();
        vita2d_swap_buffers();
    }
    if(text[text_cursor] == '_')
        text[text_cursor] = ' ';
    return strdup(text);
}

void cleanup() {
    vita2d_free_pgf(pgf);
}
