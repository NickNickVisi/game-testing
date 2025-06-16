#include <stdio.h>
#include <ncurses.h>
#include <ctime>

// has_colors(); useful

int main(void)
{
    initscr();

    refresh();

    printw("Hello, world!");

    getch();

    clear();

    printw("Goodbye, world!");

    refresh();

    getch();

    endwin();
}
