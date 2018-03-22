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

t_vector *player_drop(char **map, unsigned char team)
{
	t_vector *pos = malloc(sizeof(pos));

	if (!pos)
		return NULL;
	do {
		pos->x = rand() % MAP_SIZE.x;
		pos->y = rand() % MAP_SIZE.y;
	} while (map[pos->y][pos->x] != ' ');
	map[pos->y][pos->x] = team + '0';
	return pos;
}

void placement(char **map, t_player_info *data)
{
	map[data->pos->y][data->pos->x] = data->team_number + '0';
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

void move_to_target(t_player_info *player, char **map, short **distance_map, t_vector *pos)
{
	t_vector *next = get_next_case(distance_map, pos->y, pos->x, true);
//	int vx;
//	int vy;
	int distance = get_distance(player, pos);

	if (!next)
		return;
//	if (vx && distance > 1) {
//		player->pos->x -= (vx < 0) ? -1 : 1;
//	} else if (vy && distance > 1) {
//		player->pos->y -= (vy < 0) ? -1 : 1;
//	}
	if (distance > 1) {
		printf("from: \n\tx: %i\n\ty: %i\nto:\n\tx: %i\n\ty: %i\n", player->pos->x, player->pos->y, next->x, next->y);
		free(player->pos);
		player->pos = next;
	}
}