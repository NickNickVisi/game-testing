#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>
#include <string.h>

// has_colors(); useful

typedef struct {
    int x;
    int y;
} player;

typedef struct room_node room_node;

struct room_node {
    char **matrix;
    int width;
    int height;
    room_node *next;
};

typedef struct {
    room_node *head;
    room_node *tail;
} room_list;

static room_node *init_room(int width, int height)
{
    room_node *room = (room_node *)malloc(sizeof(room_node));

    room->width = width;
    room->height = height;
    room->matrix = malloc(height * sizeof(char *));
    for (int i =0; i < room->height; i++) {
        room->matrix[i] = malloc(width);
        memset(room->matrix[i], ' ', width);
    }
    for (int i = 0; i < width; i++)
        room->matrix[0][i] = room->matrix[height - 1][i] = '_';
    return room;
}

int main(void)
{
    char command = '\0';
    player *p = (player *)malloc(sizeof(player));
    room_node *room = init_room(20, 10);
    p->x = 3;
    p->y = 3;

    initscr();
    noecho();
    cbreak();

    while (command != 'q')
    {
        command = getch();
        room->matrix[p->y][p->x] = ' ';
        clear();
        switch(command)
        {
            case 'w': {
                if (p->y - 1 > 0)
                    p->y--;
                break;
            }
            case 's': {
                if (p->y + 1 < room->height)
                    p->y++;
                break;
            }
            case 'a': {
                if (p->x - 1 >= 0)
                    p->x--;
                break;
            }
            case 'd': {
                if (p->x + 1 < room->width)
                    p->x++;
                break;
            }
            default: {
                break;
            }
        }
        room->matrix[p->y][p->x] = 'o';
        for (int i = 0; i < room->height; i++) {
            for (int j = 0; j < room->width; j++)
                printw("%c", room->matrix[i][j]);
            addch('\n');
        }
    }
    endwin();
}
