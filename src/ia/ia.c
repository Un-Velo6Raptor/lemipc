/*
** EPITECH PROJECT, 2018
** PSU_lemipc_2017
** File description:
** Created by sahel.lucas-saoudi@epitech.eu,
*/

#include <transmission.h>
#include <stdlib.h>
#include <stdio.h>
#include "placement.h"
#include "target.h"
#include "end.h"

int ia(t_data *data)
{
	t_vector *target = NULL;
	int **distance_map = get_distance_map(data->player, data->map);

	if (data->player->pos->y == -1 || data->player->pos->x == -1) {
		player_drop(data->player, data->map);
		free_tab((void **)distance_map);
		if (!data->player->pos)
			return -1;
		distance_map = get_distance_map(data->player, data->map);
	}
	data->map[data->player->pos->y][data->player->pos->x] = ' ';
	if (is_dead(data->player, data->map)) {
		free_tab((void **)distance_map);
		return 1;
	}
	target = select_target(data, distance_map);
	move_to_target(data->player, distance_map, target);
	free_tab((void **)distance_map);
	free(target);
	return 0;
}