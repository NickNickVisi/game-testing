#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
// has_colors(); useful

/*
IDEAS:
Darkness from original
Same chase mechanics yet better room generating by using some pathfinder algorithm


*/

#define LONG_ROOM_LENGTH 64
#define SHORT_ROOM_LENGTH 32
#define TICK 60
#define MAX_RAIN 100

typedef struct {
	int x;
	int y;
} coordinates;

typedef struct {
	coordinates rain_cords;
	int not_hit;
} rain_drops;

typedef struct room_node room_node;

struct room_node {
	char **matrix;
	int width;
	int height;
	int event;
	coordinates *exit;
	coordinates *entrance;
	room_node *next;
};

typedef struct {
	room_node *head;
	room_node *tail;
} room_list;

static room_node *init_room(void)
{
	room_node *room = (room_node *)malloc(sizeof(room_node));
	int rand_length = rand() % 2;
	room->event = rand() % 4;

	room->width = rand_length ? SHORT_ROOM_LENGTH : LONG_ROOM_LENGTH;
	room->height = 10;
	room->matrix = malloc(10 * sizeof(char *));
	for (int i = 0; i < 10; i++) {
		room->matrix[i] = malloc(room->width);
		memset(room->matrix[i], ' ', room->width);
	}
	for (int i = 0; i < room->width; i++)
		room->matrix[0][i] = room->matrix[9][i] = '#';
	for (int i = 0; i < 10; i++)
		room->matrix[i][0] = room->matrix[i][room->width - 1] = '#';
	room->exit = malloc(sizeof(coordinates));
	room->entrance = malloc(sizeof(coordinates));
	room->exit->y = room->height / 2;
	room->entrance->y = room->height / 2;
	room->exit->x = room->width - 1;
	room->entrance->x = 0;
	switch (room->event) {
		case 1: {
			room->entrance->x = room->width - 1;
			room->exit->x = 0;
		}
	}
	room->matrix[5][room->width - 1] = room->matrix[5][0] = ' ';
	room->next = '\0';
	return room;
}

static room_list *generate_list(void)
{
	int counter = 4;
	room_list *list = malloc(sizeof(room_list));

	list->head = init_room();
	room_node *current = list->head;
	while(counter) {
		current->next = init_room();
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

static unsigned current_time(void)
{
	struct timespec ts;
    clock_gettime(1, &ts);
    return (ts.tv_sec * 1000UL) + (ts.tv_nsec / 1000000UL);
}

static void spawn_rain(int width, rain_drops *rain)
{
	for (int i = 0; i < MAX_RAIN; i++) {
        if (!rain[i].not_hit) {
            rain[i].rain_cords.x = rand() % width - 1;
			if (!rain[i].rain_cords.x)
				rain[i].rain_cords.x = 1;
            rain[i].rain_cords.y = 2;
            rain[i].not_hit = 1;
            break;
        }
    }
}

static void update_rain(room_node *room, rain_drops *rain) {
	spawn_rain(room->width, rain);
	for (int i = 0; i < MAX_RAIN; i++) {
        if (rain[i].not_hit) {
			int x = rain[i].rain_cords.x;
			int y = rain[i].rain_cords.y;
            mvaddch(y, x, room->matrix[y - 1][x]);
            y = ++rain[i].rain_cords.y;
			x = --rain[i].rain_cords.x;
            if (y >= 10 || x == 0 || room->matrix[y - 1][x] == 'o')
                rain[i].not_hit = 0;
            else
                mvaddch(y, x, '/');
        }
    }
}

static void flashlight(coordinates *p, room_node *room, int x, int y, int radius)
{
	if (!radius || x < 0 || y < 0 || y >= 10 || x >= room->width) {
		return;
	}
	int dx = x - p->x;
	int dy = y - p->y;
	int sqr_distance = dx * dx + dy * dy;
	int sqr_rad = radius * radius;

	if (sqr_distance > sqr_rad) 
		mvaddch(y + 1, x, '#');
	else
		mvaddch(y + 1, x, room->matrix[y][x]);

	flashlight(p, room, x + 1, y, radius - 1);
	flashlight(p, room, x, y + 1, radius - 1);
	flashlight(p, room, x - 1, y, radius - 1);
	flashlight(p, room, x, y - 1, radius - 1);
}

int main(void)
{
	coordinates *p = malloc(sizeof(coordinates));

	initscr();
	nodelay(stdscr, TRUE);
	noecho();
	cbreak();
	curs_set(0);
	srand(time(0));
	int counter = 0;
	unsigned long last_tick = current_time();
	char command = '\0';
	room_list *list = generate_list();

	printw("%d\n", counter);
	if (list->head->event != 3) {
		for (int i = 0; i < list->head->height; i++) {
			for (int j = 0; j < list->head->width; j++)
				addch(list->head->matrix[i][j]);
			addch('\n');
		}
	} else {
		for (int i = 0; i < list->head->height; i++) {
			for (int j = 0; j < list->head->width; j++)
				addch('#');
			addch('\n');
		}
	}
	p->x = list->head->entrance->x;
	p->y = list->head->entrance->y;
	mvaddch(p->y + 1, p->x, 'o');
	refresh();
	int running = 1;
	rain_drops *rain = malloc(sizeof(rain_drops) * MAX_RAIN);

	while(running && command != 'q')
	{
		unsigned long now = current_time();
		command = getch();
		
		if (command != -1) {
			mvaddch(p->y + 1, p->x, ' ');
			list->head->matrix[p->y][p->x] = ' ';
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
			if (list->head->event == 3) {
				flashlight(p, list->head, p->x, p->y, 4);
			}
			list->head->matrix[p->y][p->x] = 'o';
			mvaddch(p->y + 1, p->x, 'o');
		}
		if (now - last_tick >= TICK) {
			last_tick = now;
			if (list->head->event == 2) {
				update_rain(list->head, rain);
			}
		}
		if (p->x == list->head->exit->x && p->y == list->head->exit->y) {
			room_node *delete = list->head;

			if (list->head->next) {
				list->head = list->head->next;
				free_list_node(delete);
			}
			if (!(counter % 5)) {
				free_list(list);
				list = generate_list();
			}
			for (int i = 0; i < MAX_RAIN; i++) {
				rain[i].not_hit = 0;
			}
			clear();
			counter++;
			printw("%d\n", counter);
			if (list->head->event != 3) {
				for (int i = 0; i < list->head->height; i++) {
					for (int j = 0; j < list->head->width; j++)
						addch(list->head->matrix[i][j]);
					addch('\n');
				}
			} else {
				for (int i = 0; i < list->head->height; i++) {
					for (int j = 0; j < list->head->width; j++)
						addch('#');
					addch('\n');
				}
			}
			p->x = list->head->entrance->x;
			p->y = list->head->entrance->y;
			mvaddch(p->y + 1, p->x, 'o');
		}
		refresh();
	}
	free(p);
	free_list(list);
	endwin();
}
