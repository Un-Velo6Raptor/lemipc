/*
** EPITECH PROJECT, 2018
** PSU_lemipc_2017
** File description:
** Created by sahel.lucas-saoudi@epitech.eu,
*/

#include <stdio.h>
#include <transmission.h>
#include <config.h>

static int is_enemy(t_player_info *player, char **map, int y, int x)
{
	if (y >= MAP_SIZE.y || y < 0 || x >= MAP_SIZE.x || x < 0) {
		return 0;
	}
	if (map[y][x] != ' ' && map[y][x] != player->team_number + '0')
		return 1;
	return 0;
}

bool is_dead(t_player_info *player, char **map)
{
	t_vector *pos = player->pos;
	int nb = 0;

	nb += is_enemy(player, map, pos->y, pos->x + 1);
	nb += is_enemy(player, map, pos->y, pos->x - 1);
	nb += is_enemy(player, map, pos->y + 1, pos->x);
	nb += is_enemy(player, map, pos->y - 1, pos->x);
	nb += is_enemy(player, map, pos->y + 1, pos->x + 1);
	nb += is_enemy(player, map, pos->y + 1, pos->x - 1);
	nb += is_enemy(player, map, pos->y - 1, pos->x + 1);
	nb += is_enemy(player, map, pos->y - 1, pos->x - 1);
	return nb > 1 ? true : false;
}