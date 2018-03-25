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
			can = (map[y][x] == ' ') ? (true) : (can);
		}
	}
	return can;
}

void player_drop(t_player_info *player, char **map)
{
	t_vector *pos = malloc(sizeof(pos));

	if (!pos || !can_drop(map)) {
		free(player->pos);
		fprintf(stderr, "Player can't drop\n");
		player->pos = NULL;
		return;
	}
	do {
		pos->x = rand() % MAP_SIZE.x;
		pos->y = rand() % MAP_SIZE.y;
	} while (map[pos->y][pos->x] != ' ');
	map[pos->y][pos->x] = player->team_number;
	free(player->pos);
	player->pos = pos;
}

void placement(char **map, t_player_info *data)
{
	map[data->pos->y][data->pos->x] = data->team_number;
}

t_vector *get_next_case(int **map, int y, int x, bool st)
{
	t_vector *pos = malloc(sizeof(t_vector));
	t_vector *ret = NULL;
	int act = map[y][x];

	if (!pos)
		return NULL;
	act = act == -2 && st ? get_distance_at(map, y, x) + 1 : act;
	pos->y = y;
	pos->x = x;
	if (act != 1 && x > 0 && map[y][x - 1] == act - 1)
		ret = get_next_case(map, y, x - 1, false);
	if (!ret && act != 1 && x < MAP_SIZE.x - 1 && map[y][x + 1] == act - 1)
		ret = get_next_case(map, y, x + 1, false);
	if (!ret && act != 1 && y > 0 && map[y - 1][x] == act - 1)
		ret = get_next_case(map, y - 1, x, false);
	if (!ret && act != 1 && y < MAP_SIZE.y - 1 && map[y + 1][x] == act - 1)
		ret = get_next_case(map, y + 1, x, false);
	if (ret)
		free(pos);
	return (ret) ? ret : pos;
}

void move_to_target(t_player_info *player, int **distance_map, t_vector *pos)
{
	t_vector *next = NULL;
	int distance;

	if (!pos)
		return;
	next = get_next_case(distance_map, pos->y, pos->x, true);
	distance = get_distance(player, pos);
	if (!next)
		return;
	if (distance > 1) {
		free(player->pos);
		player->pos = next;
	}
}