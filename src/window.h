#include <iostream>
#include <ncurses.h>

WINDOW *create_newwin(char borderVertical, char borderOrizontal);
void destroy_win(WINDOW *local_win);
void initWinScreen();