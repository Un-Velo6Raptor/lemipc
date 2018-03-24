/*
** EPITECH PROJECT, 2018
** PSU_lemipc_2017
** File description:
** Created by sahel.lucas-saoudi@epitech.eu,
*/

#include <stdlib.h>
#include <stdio.h>
#include "transmission.h"
#include "config.h"
#include "target.h"

bool can_drop(char **map)
{
	bool can = false;

	for (int y = 0; y < MAP_SIZE.y; y++) {
		for (int x = 0; x < MAP_SIZE.x; x++) {
			can = (map[y][x] == ' ') ? (true) : (false);
		}
	}
	return can;
}

t_vector *player_drop(char **map, unsigned char team)
{
	t_vector *pos = malloc(sizeof(pos));

	if (!pos || !can_drop(map)) {
		fprintf(stderr, "Player can't drop\n");
		return NULL;
	}
	do {
		pos->x = rand() % MAP_SIZE.x;
		pos->y = rand() % MAP_SIZE.y;
	} while (map[pos->y][pos->x] != ' ');
	map[pos->y][pos->x] = team;
	return pos;
}

void placement(char **map, t_player_info *data)
{
	map[data->pos->y][data->pos->x] = data->team_number;
}

t_vector *get_next_case(short **distance_map, int y, int x, bool first)
{
	t_vector *pos = malloc(sizeof(t_vector));
	short act = distance_map[y][x];

	if (!pos)
		return NULL;
	if (act == -2 && first == true)
		act = get_distance_at(distance_map, y, x) + 1;
	pos->y = y;
	pos->x = x;
	if (act == 1)
		return pos;
	if (x > 0 && distance_map[y][x - 1] == act - 1) {
		free(pos);
		return get_next_case(distance_map, y, x - 1, false);
	}
	if (x < MAP_SIZE.x - 1 && distance_map[y][x + 1] == act - 1) {
		free(pos);
		return get_next_case(distance_map, y, x + 1, false);
	}
	if (y > 0 && distance_map[y - 1][x] == act - 1) {
		free(pos);
		return get_next_case(distance_map, y - 1, x, false);
	}
	if (y < MAP_SIZE.y - 1 && distance_map[y + 1][x] == act - 1) {
		free(pos);
		return get_next_case(distance_map, y + 1, x, false);
	}
	return pos;
}

void move_to_target(t_player_info *player, short **distance_map, t_vector *pos)
{
	t_vector *next = get_next_case(distance_map, pos->y, pos->x, true);
	int distance = get_distance(player, pos);

	if (!next)
		return;
	if (distance > 1) {
		free(player->pos);
		player->pos = next;
	}
}