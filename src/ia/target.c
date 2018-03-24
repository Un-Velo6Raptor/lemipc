/*
** EPITECH PROJECT, 2018
** PSU_lemipc_2017
** File description:
** Created by sahel.lucas-saoudi@epitech.eu,
*/

#include <config.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "transmission.h"

unsigned int get_distance(t_player_info *player, t_vector *pos)
{
	return (abs(player->pos->x - pos->x) + abs(player->pos->y - pos->y));
}

short get_distance_at(short **map, int y, int x)
{
	short left = (x > 0 && x < MAP_SIZE.x) ? map[y][x - 1] : -1;
	short right = (x >= 0 && x < MAP_SIZE.x - 1) ? map[y][x + 1] : -1;
	short top = (y > 0 && y < MAP_SIZE.y) ? map[y - 1][x] : -1;
	short bot = (y >= 0 && y < MAP_SIZE.y - 1) ? map[y + 1][x] : -1;
	short ret = left;

	if ((right < ret && right >= 0) || ret < 0)
		ret = right;
	if ((top < ret && top >= 0) || ret < 0)
		ret = top;
	if ((bot < ret && bot >= 0) || ret < 0)
		ret = bot;
	return ret;
}

static t_vector *get_nearest(t_player_info *player, char **map, short **distance_map)
{
	t_vector *tmp = malloc(sizeof(t_vector));
	short distance = MAP_SIZE.x + MAP_SIZE.y;

	if (!tmp || !distance_map)
		return NULL;
	tmp->x = -1;
	tmp->y = -1;
	for (int y = 0; y < MAP_SIZE.y; y++) {
		for (int x = 0; x < MAP_SIZE.x; x++) {
			if (map[y][x] != ' ' && map[y][x] != player->team_number
				&& map[y][x] > 0
				&& get_distance_at(distance_map, y, x) < distance &&
				get_distance_at(distance_map, y, x) >= 0) {
				distance = get_distance_at(distance_map, y, x);
				tmp->x = x;
				tmp->y = y;
			}
		}
	}
	if (tmp->x == -1 || tmp->y == -1) {
		free(tmp);
		return NULL;
	}
	return tmp;
}

void display_distancemap(short **distance_map)
{
	for (int i = 0; i < MAP_SIZE.y; i++) {
		for (int j = 0; j < MAP_SIZE.x; j++) {
			printf("%i ", distance_map[i][j]);
		}
		printf("\n");
	}
}

static void set_distance(t_player_info *player, short **distance_map, char **map, t_vector *pos)
{
	short distance;
	t_vector dir = {pos->x - 1, pos->y};

	if (pos->y < 0 || pos->y >= MAP_SIZE.y || pos->x < 0 || pos->x >= MAP_SIZE.x)
		return;
	if (player->pos->x == pos->x && player->pos->y == pos->y) {
		distance_map[pos->y][pos->x] = 0;
	}
	else {
		if (map[pos->y][pos->x] < 0) {
			distance_map[pos->y][pos->x] = map[pos->y][pos->x];
			return;
		} else if (map[pos->y][pos->x] != ' ') {
			distance_map[pos->y][pos->x] = -2;
			return;
		}
		distance = get_distance_at(distance_map, pos->y, pos->x) + (short) 1;
		if (distance_map[pos->y][pos->x] <= distance &&
			distance != 0 && distance_map[pos->y][pos->x] != -1)
			return;
		distance_map[pos->y][pos->x] = distance;
	}
	set_distance(player, distance_map, map, &dir);
	dir.x = pos->x + 1;
	set_distance(player, distance_map, map, &dir);
	dir.x = pos->x;
	dir.y = pos->y - 1;
	set_distance(player, distance_map, map, &dir);
	dir.y = pos->y + 1;
	set_distance(player, distance_map, map, &dir);
}

short **get_distance_map(t_player_info *player, char **map)
{
	short **distance_map = malloc(sizeof(short *) * (MAP_SIZE.y + 1));

	if (!distance_map)
		return NULL;
	for (int i = 0; i < MAP_SIZE.y; i++) {
		distance_map[i] = malloc(sizeof(short) * (MAP_SIZE.x + 1));
		if (!distance_map[i])
			return NULL;
		for (int j = 0; j < MAP_SIZE.x; j++)
			distance_map[i][j] = -1;
		distance_map[i][MAP_SIZE.x] = '\0';
	}
	distance_map[MAP_SIZE.y] = NULL;
	set_distance(player, distance_map, map, player->pos);
	return distance_map;
}

t_vector *select_target(t_player_info *player, char **map, short **distance_map)
{
	t_vector *nearest = get_nearest(player, map, distance_map);

	return nearest;
}