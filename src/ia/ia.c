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

int ia(t_player_info *player, char **map)
{
	t_vector *target = NULL;
	short **distance_map = get_distance_map(player, map);

	if (player->pos->y == -1 || player->pos->x == -1) {
		free(player->pos);
		player->pos = player_drop(map, player->team_number);
		free_tab((void **)distance_map);
		distance_map = get_distance_map(player, map);
		if (!player->pos)
			return -1;
	}
	map[player->pos->y][player->pos->x] = ' ';
	if (is_dead(player, map)) {
		free_tab((void **) distance_map);
		return 1;
	}
	target = select_target(player, map, distance_map);
	if (target)
		move_to_target(player, distance_map, target);
	placement(map, player);
	free(target);
	free_tab((void **)distance_map);
	return 0;
}