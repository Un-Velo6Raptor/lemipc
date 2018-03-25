/*
** EPITECH PROJECT, 2018
** PSU_lemipc_2017
** File description:
** Created by sahel.lucas-saoudi@epitech.eu,
*/

#include <unistd.h>
#include <stdlib.h>
#include "transmission.h"
#include "target.h"
#include "config.h"

static int preset_distance(char **map, int **distance_map,
	t_vector *pos)
{
	int distance;

	if (map[pos->y][pos->x] != ' ') {
		distance_map[pos->y][pos->x] =
			map[pos->y][pos->x] < 0 ? map[pos->y][pos->x] : -2;
		return 1;
	}
	distance = get_distance_at(distance_map, pos->y, pos->x) + 1;
	if (distance_map[pos->y][pos->x] <= distance &&
		distance != 0 && distance_map[pos->y][pos->x] != -1)
		return 1;
	distance_map[pos->y][pos->x] = distance;
	return 0;
}

static void set_distance(t_player_info *player, int **distance_map, char **map,
	t_vector *pos
)
{
	t_vector dir = {pos->x - 1, pos->y};

	if (pos->y < 0 || pos->y >= MAP_SIZE.y || pos->x < 0 ||
		pos->x >= MAP_SIZE.x)
		return;
	if (player->pos->x == pos->x && player->pos->y == pos->y) {
		distance_map[pos->y][pos->x] = 0;
	} else if (preset_distance(map, distance_map, pos))
		return;
	set_distance(player, distance_map, map, &dir);
	dir = (t_vector){pos->x + 1, pos->y};
	set_distance(player, distance_map, map, &dir);
	dir = (t_vector){pos->x, pos->y - 1};
	set_distance(player, distance_map, map, &dir);
	dir = (t_vector){pos->x, pos->y + 1};
	set_distance(player, distance_map, map, &dir);
}

int **get_distance_map(t_player_info *player, char **map)
{
	int **distance_map = malloc(sizeof(int *) * (MAP_SIZE.y + 1));

	if (!distance_map)
		return NULL;
	for (int i = 0; i < MAP_SIZE.y; i++) {
		distance_map[i] = malloc(sizeof(int) * (MAP_SIZE.x + 1));
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