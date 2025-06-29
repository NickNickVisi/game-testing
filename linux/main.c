#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>
#include <string.h>

// has_colors(); useful

/*
IDEAS:
Effects for outside rooms (rain), probably use some other function that sets a certain part of the screen, also randomly generated and drops disappear upon touching player
Darkness from original
Same chase mechanics yet better room generating by using some pathfinder algorithm


*/

#define LONG_ROOM_LENGTH 64
#define SHORT_ROOM_LENGTH 32


typedef struct {
	int x;
	int y;
} coordinates;

typedef struct room_node room_node;

struct room_node {
	char **matrix;
	int width;
	int height;
	coordinates *exit;
	coordinates *entrance;
	room_node *next;
};

typedef struct {
	room_node *head;
	room_node *tail;
} room_list;

static room_node *init_room(int height)
{
	room_node *room = (room_node *)malloc(sizeof(room_node));
	int rand_length = rand() % 2;
	int rand_event = rand() % 2;

	room->width = rand_length ? SHORT_ROOM_LENGTH : LONG_ROOM_LENGTH;
	room->height = height;
	room->matrix = malloc(height * sizeof(char *));
	for (int i = 0; i < height; i++) {
		room->matrix[i] = malloc(room->width);
		memset(room->matrix[i], ' ', room->width);
	}
	for (int i = 0; i < room->width; i++)
		room->matrix[0][i] = room->matrix[height - 1][i] = '#';
	for (int i = 0; i < height; i++)
		room->matrix[i][0] = room->matrix[i][room->width - 1] = '#';
	room->exit = malloc(sizeof(coordinates));
	room->entrance = malloc(sizeof(coordinates));
	room->exit->y = room->height / 2;
	room->entrance->y = room->height / 2;
	if(!rand_event) {
		room->entrance->x = room->width - 1;
		room->exit->x = 0;
	} else {
		room->exit->x = room->width - 1;
		room->entrance->x = 0;
	}
	room->matrix[height / 2][room->width - 1] = room->matrix[height / 2][0] = ' ';
	room->next = '\0';
	return room;
}

static room_list *generate_list(void)
{
	int counter = 4;
	room_list *list = malloc(sizeof(room_list));

	list->head = init_room(10);
	room_node *current = list->head;
	while(counter) {
		current->next = init_room(10);
		current = current->next;
		counter--;
	}
	list->tail = current;
	current->next = '\0';
	return list;
}

static void free_list_node(room_node *room)
{
	for (int i = 0; i < room->height; i++)
		free(room->matrix[i]);
	free(room->matrix);
	free(room->entrance);
	free(room->exit);
	free(room);
}

static void free_list(room_list *list)
{
	room_node *current = list->head;

	while (current) {
		list->head = list->head->next;
		free_list_node(current);
		current = list->head;
	}
	free(list);
}

int main(void)
{
	coordinates *p = malloc(sizeof(coordinates));

	initscr();
	noecho();
	cbreak();
	srand(time(0));
	char command = '\0';
	int counter = 0;
	room_list *list = generate_list();

	p->x = list->head->entrance->x;
	p->y = list->head->entrance->y;
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
				if (list->head->matrix[p->y - 1][p->x] == ' ')
					p->y--;
				break;
			}
			case 's': {
				if (list->head->matrix[p->y + 1][p->x] == ' ')
					p->y++;
				break;
			}
			case 'a': {
				if (list->head->matrix[p->y][p->x - 1] == ' ')
					p->x--;
				break;
			}
			case 'd': {
				if (list->head->matrix[p->y][p->x + 1] == ' ')
					p->x++;
				break;
			}
		}
		if (p->x == list->head->exit->x && p->y == list->head->exit->y) {
			counter++;
			room_node *clear = list->head;

			if (list->head->next) {
				list->head = list->head->next;
				free_list_node(clear);
			}
			if (!(counter % 5)) {
				free_list(list);
				list = generate_list();
				printw("Generated new room list.\n");
			}
			p->x = list->head->entrance->x;
			p->y = list->head->entrance->y;
		}
	}
	free(p);
	free_list(list);
	endwin();
}
