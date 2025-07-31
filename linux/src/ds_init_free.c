#include "../include/data_structures.h"

room_node *init_room(void)
{
	room_node *room = (room_node *)malloc(sizeof(room_node));
	room->event = rand() % 4;

	room->width = rand() % 2 ? SHORT_ROOM_LENGTH : LONG_ROOM_LENGTH;
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

room_list *generate_list(void)
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

void free_list_node(room_node *room)
{
	for (int i = 0; i < room->height; i++)
		free(room->matrix[i]);
	free(room->matrix);
	free(room->entrance);
	free(room->exit);
	free(room);
}

void free_list(room_list *list)
{
	room_node *current = list->head;

	while (current) {
		list->head = list->head->next;
		free_list_node(current);
		current = list->head;
	}
	free(list);
}
