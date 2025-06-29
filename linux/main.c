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
		room->matrix[0][i] = room->matrix[height - 1][i] = '#';
	for (int i = 0; i < height; i++)
		room->matrix[i][0] = room->matrix[i][width - 1] = '#';
	return room;
}

static room_list *generate_list(void)
{
	int counter = 4;
	room_list *list = malloc(sizeof(room_list));

	list->head = init_room(20, 10);
	room_node *current = list->head;
	while(counter) {
		current->next = init_room(20, 10);
		current = current->next;
		counter--;
	}
	list->tail = current;
	current->next = '\0';
	return list;
}

int main(void)
{
	player *p = (player *)malloc(sizeof(player));
	p->x = 3;
	p->y = 3;

	initscr();
	noecho();
	cbreak();

	char command = '\0';
	int counter = 0;
	room_list *list = generate_list();

	while(command != 'q')
	{
		printw("%d\n", counter);
		list->head->matrix[p->y][p->x] = 'o';
		for (int i = 0; i < list->head->height; i++) {
			for (int j = 0; j < list->head->width; j++)
				addch(list->head->matrix[i][j]); // printw if no longer efficient
			addch('\n');
		}
		command = getch();
		list->head->matrix[p->y][p->x] = ' ';
		clear();
		switch(command)
		{
			case 'w': {
				if (p->y - 1 > 0)
					p->y--;
				break;
			}
			case 's': {
				if (p->y + 1 < list->head->height - 1)
					p->y++;
				break;
			}
			case 'a': {
				if (p->x - 1 > 0)
					p->x--;
				break;
			}
			case 'd': {
				if (p->x + 1 < list->head->width - 1)
					p->x++;
				break;
			}
			default: {
				counter++;
				room_node *clear = list->head;
				if (list->head->next)
					list->head = list->head->next;
				else {
					clear = list->head;
				}
				for (int i = 0; i < clear->height; i++) {
					free(clear->matrix[i]);
				}
				free(clear->matrix);
				free(clear);
				if (counter == 4) {
					command = 'q';
				}
				break;
			}
		}
	}
	free(p);
	free(list);
	endwin();
}
