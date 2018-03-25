/*
** EPITECH PROJECT, 2018
** PSU_lemipc_2017
** File description:
** Created by sahel.lucas-saoudi@epitech.eu,
*/

#include <config.h>
#include <stdlib.h>
#include <string.h>
#include "transmission.h"

unsigned int get_distance(t_player_info *player, t_vector *pos)
{
	return (abs(player->pos->x - pos->x) + abs(player->pos->y - pos->y));
}

int get_distance_at(int **map, int y, int x)
{
	int left = (x > 0 && x < MAP_SIZE.x) ? map[y][x - 1] : -1;
	int right = (x >= 0 && x < MAP_SIZE.x - 1) ? map[y][x + 1] : -1;
	int top = (y > 0 && y < MAP_SIZE.y) ? map[y - 1][x] : -1;
	int bot = (y >= 0 && y < MAP_SIZE.y - 1) ? map[y + 1][x] : -1;
	int ret = left;

	if ((right < ret && right >= 0) || ret < 0)
		ret = right;
	if ((top < ret && top >= 0) || ret < 0)
		ret = top;
	if ((bot < ret && bot >= 0) || ret < 0)
		ret = bot;
	return ret;
}

static void check_nearest(t_data *data, int **distance_map, t_vector **vec,
	int *dist
)
{
	if (data->map[vec[1]->y][vec[1]->x] != ' ' &&
		data->map[vec[1]->y][vec[1]->x] != data->player->team_number &&
		data->map[vec[1]->y][vec[1]->x] > 0 &&
		get_distance_at(distance_map, vec[1]->y, vec[1]->x) < *dist &&
		get_distance_at(distance_map, vec[1]->y, vec[1]->x) >= 0) {
		*dist = get_distance_at(distance_map, vec[1]->y, vec[1]->x);
		fill_vector(vec[0], vec[1]->x, vec[1]->y);
	}
}

static t_vector *get_nearest(t_data *data, int **distance_map)
{
	t_vector *tmp[2] = {malloc(sizeof(t_vector)), &(t_vector){0, 0}};
	int distance = MAP_SIZE.x + MAP_SIZE.y;

	if (!tmp[0] || !distance_map)
		return NULL;
	fill_vector(tmp[0], -1, -1);
	for (tmp[1]->y = 0; tmp[1]->y < MAP_SIZE.y; tmp[1]->y++) {
		for (tmp[1]->x = 0; tmp[1]->x < MAP_SIZE.x; tmp[1]->x++) {
			check_nearest(data, distance_map, tmp, &distance);
		}
	}
	if (tmp[0]->x == -1 || tmp[0]->y == -1) {
		free(tmp[0]);
		return NULL;
	}
	return tmp[0];
}

t_vector *select_target(t_data *data, int **distance_map)
{
	t_vector *nearest = get_nearest(data, distance_map);

	return nearest;
}