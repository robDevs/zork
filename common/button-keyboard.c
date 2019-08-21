#include "button-keyboard.h"
#include "controls.h"

charKey keys[26];
vita2d_pgf *keys_pgf;
int cursor;
int frame;

void init_keyboard() {
    keys_pgf = vita2d_load_default_pgf(); //font used by keyboard.
    cursor = 0;
    frame = 0;

    int x = 6;
    int y = 544-162; // the positions for the keys.
    for(int i = 0; i < 26; i++) {
        keys[i].x = x;
        keys[i].y = y;
        x += 95;
        if(i == 9) {
            x = 6+91/2;
            y += 54;
        }
        if(i == 18) {
            x = 6+91/2+95;
            y += 54;
        }
    }

    set_key_chars(frame);
}

void set_key_chars(int option){
    if(option == 0) {
        keys[0].print_name = 'q';
        keys[1].print_name = 'w';
        keys[2].print_name = 'e';
        keys[3].print_name = 'r';
        keys[4].print_name = 't';
        keys[5].print_name = 'y';
        keys[6].print_name = 'u';
        keys[7].print_name = 'i';
        keys[8].print_name = 'o';
        keys[9].print_name = 'p';
        keys[10].print_name = 'a';
        keys[11].print_name = 's';
        keys[12].print_name = 'd';
        keys[13].print_name = 'f';
        keys[14].print_name = 'g';
        keys[15].print_name = 'h';
        keys[16].print_name = 'j';
        keys[17].print_name = 'k';
        keys[18].print_name = 'l';
        keys[19].print_name = 'z';
        keys[20].print_name = 'x';
        keys[21].print_name = 'c';
        keys[22].print_name = 'v';
        keys[23].print_name = 'b';
        keys[24].print_name = 'n';
        keys[25].print_name = 'm';
    }
    else if(option == 1) {
        keys[0].print_name = '~';
        keys[1].print_name = '`';
        keys[2].print_name = '!';
        keys[3].print_name = '@';
        keys[4].print_name = '#';
        keys[5].print_name = '$';
        keys[6].print_name = '%';
        keys[7].print_name = '^';
        keys[8].print_name = '&';
        keys[9].print_name = '*';
        keys[10].print_name = '(';
        keys[11].print_name = ')';
        keys[12].print_name = '{';
        keys[13].print_name = '}';
        keys[14].print_name = '+';
        keys[15].print_name = '=';
        keys[16].print_name = '[';
        keys[17].print_name = ']';
        keys[18].print_name = '_';
        keys[19].print_name = '-';
        keys[20].print_name = ':';
        keys[21].print_name = ';';
        keys[22].print_name = '"';
        keys[23].print_name = '\'';
        keys[24].print_name = '?';
        keys[25].print_name = '/';
    }
    else if(option == 2) {
        keys[0].print_name = '1';
        keys[1].print_name = '2';
        keys[2].print_name = '3';
        keys[3].print_name = '4';
        keys[4].print_name = '5';
        keys[5].print_name = '6';
        keys[6].print_name = '7';
        keys[7].print_name = '8';
        keys[8].print_name = '9';
        keys[9].print_name = '0';
        keys[10].print_name = '<';
        keys[11].print_name = '>';
        keys[12].print_name = ',';
        keys[13].print_name = '.';
        keys[14].print_name = '|';
        keys[15].print_name = '\\';
        keys[16].print_name = '[';
        keys[17].print_name = ']';
        keys[18].print_name = '_';
        keys[19].print_name = '-';
        keys[20].print_name = ':';
        keys[21].print_name = ';';
        keys[22].print_name = '"';
        keys[23].print_name = '\'';
        keys[24].print_name = '?';
        keys[25].print_name = '/';
    }
}

char *keyboard_get(int max) {
    reset_keys();
    int done = 0;

    int text_cursor = 0;

    init_keys();

    char text[100] = "_";

    sceTouchSetSamplingState(SCE_TOUCH_PORT_FRONT, 1);
    sceTouchEnableTouchForce(SCE_TOUCH_PORT_FRONT);
    SceTouchData touch_old[SCE_TOUCH_PORT_MAX_NUM];
	SceTouchData touch[SCE_TOUCH_PORT_MAX_NUM];

    int wait = 0; //getting touch on first few loops maybe?

    while(done == 0) {
        update_keys();
        memcpy(touch_old, touch, sizeof(touch_old));

        sceTouchPeek(0, &touch[0], 1);

        if(select_released) {
            frame += 1;
            if(frame > 2)
                frame = 0;
            set_key_chars(frame);
        }
        if(wait < 5) wait++;
        //check for a press
        if(touch_old[SCE_TOUCH_PORT_FRONT].reportNum > 0 && wait >= 5) {
            for(int i = 0; i < 26; i++) {
                if((touch[SCE_TOUCH_PORT_FRONT].report[0].y/2 >= keys[i].y)
                && (touch[SCE_TOUCH_PORT_FRONT].report[0].y/2 <= keys[i].y + 50)
                && (touch[SCE_TOUCH_PORT_FRONT].report[0].x/2 >= keys[i].x)
                && (touch[SCE_TOUCH_PORT_FRONT].report[0].x/2 <= keys[i].x + 91))
                {
                    cursor = i;
                }
            }
        }
        //check for a release
        if(touch[SCE_TOUCH_PORT_FRONT].reportNum == 0 && touch_old[SCE_TOUCH_PORT_FRONT].reportNum > 0 && wait >= 5) {
            for(int i = 0; i < 26; i++) {
                if((touch[SCE_TOUCH_PORT_FRONT].report[0].y/2 >= keys[i].y)
                && (touch[SCE_TOUCH_PORT_FRONT].report[0].y/2 <= keys[i].y + 50)
                && (touch[SCE_TOUCH_PORT_FRONT].report[0].x/2 >= keys[i].x)
                && (touch[SCE_TOUCH_PORT_FRONT].report[0].x/2 <= keys[i].x + 91))
                {
                    cursor = i;
                    if(text_cursor < max) {
                        text[text_cursor] = keys[i].print_name;
                        text_cursor += 1;
                        text[text_cursor] = '_';
                    }
                }
            }
        }

        if(start_released)
            done = 1;
        if(left_pressed){
            if(cursor == 0)
                cursor += 9;
            else if(cursor == 10)
                cursor += 8;
            else if(cursor == 19)
                cursor += 6;
            else
                cursor -= 1;
        }
        if(right_pressed) {
            if(cursor == 9)
                cursor -= 9;
            else if(cursor == 18)
                cursor -= 8;
            else if(cursor == 25)
                cursor -= 6;
            else
                cursor += 1;
        }
        if(up_pressed) {
            if(cursor < 8 && cursor > 0)
                cursor += 18;
            else if(cursor == 0)
                cursor += 19;
            else if(cursor == 8 || cursor == 9)
                cursor = 25;
            else if(cursor < 18)
                cursor -= 10;
            else if(cursor == 18)
                cursor -= 10;
            else if(cursor >= 19)
                cursor -= 8;
        }
        if(down_pressed) {
            if(cursor < 10)
                cursor += 10;
            else if(cursor < 18 && cursor > 10)
                cursor += 8;
            else if(cursor == 10)
                cursor += 9;
            else if(cursor == 18)
                cursor += 7;
            else if(cursor >= 19)
                cursor -= 18;
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

        draw_keys(text);

        vita2d_end_drawing();
        vita2d_swap_buffers();
    }
    if(text[text_cursor] == '_')
        text[text_cursor] = ' ';
    return strdup(text);
}

void draw_keys(char *text) {
    vita2d_draw_rectangle(0, 544-162-30, 960, 162+30, RGBA8(190,190,190,255));

    vita2d_pgf_draw_textf(keys_pgf, 960/2-vita2d_pgf_text_width(keys_pgf, 1.0f, text)/2, 544-162-10, RGBA8(0,0,0,255), 1.0f, ">%s", text);

    for(int i = 0; i < 26; i++) {
        draw_key(keys[i], cursor == i);
    }
}

void keyboard_cleanup() {
    vita2d_free_pgf(keys_pgf);
}

void draw_key(charKey key, bool selected) {
    if(!selected)
        vita2d_draw_rectangle(key.x, key.y, 91, 50, RGBA8(0,0,0,255));
    else
        vita2d_draw_rectangle(key.x, key.y, 91, 50, RGBA8(130,130,130,255));

    vita2d_pgf_draw_textf(keys_pgf, key.x+91/2-vita2d_pgf_text_width(keys_pgf, 1.0f, &key.print_name)/2, key.y+25+vita2d_pgf_text_height(keys_pgf, 1.0f, &key.print_name)/2, RGBA8(255,255,255,255), 1.0f, "%c", key.print_name);
}
