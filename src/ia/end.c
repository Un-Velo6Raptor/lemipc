/*
** EPITECH PROJECT, 2018
** PSU_lemipc_2017
** File description:
** Created by sahel.lucas-saoudi@epitech.eu,
*/

#include <stdio.h>
#include "transmission.h"
#include "sys/sem.h"
#include "config.h"

static int is_enemy(t_player_info *player, char **map, int y, int x)
{
	if (y >= MAP_SIZE.y || y < 0 || x >= MAP_SIZE.x || x < 0) {
		return 0;
	}
	if (map[y][x] != ' ' && map[y][x] != player->team_number + '0' && map[y][x] > 0)
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

bool ended(char **map)
{
	char team = ' ';
	bool found = false;
	bool end = true;

	for (int y = 0; y < MAP_SIZE.y; y++) {
		for (int x = 0; x < MAP_SIZE.x; x++) {
			end = (found == true && map[y][x] != team && map[y][x] != ' ' && map[y][x] > 0) ? false : end;
			found = (found == false && map[y][x] != team && map[y][x] > 0) ? true : found;
			team = map[y][x] != ' ' && map[y][x] > 0 ? map[y][x] : team;
		}
	}
	return (end);
}

int end_game(t_data *data, char **map, struct sembuf *sops, int ret)
{
	printf("--END\n");
	display_tab(map);
	if (map && set_new_map(data, map) == 84)
		ret = 84;
	sops->sem_op = 1;
	semop(data->sem_id, sops, 1);
	if (map)
		free_tab(map);
	return ret;
}