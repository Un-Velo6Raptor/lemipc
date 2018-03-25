/*
** EPITECH PROJECT, 2018
** PSU_lemipc_2017
** File description:
** Created by sahel.lucas-saoudi@epitech.eu,
*/

#include <string.h>
#include "transmission.h"
#include "sys/sem.h"
#include "config.h"

static size_t is_enemy(t_player_info *player, char **map, int y, int x)
{
	if (y >= MAP_SIZE.y || y < 0 || x >= MAP_SIZE.x || x < 0) {
		return strlen(TEAMS);
	}
	if (map[y][x] != ' ' && map[y][x] != player->team_number &&
		map[y][x] > 0)
		return (unsigned int)map[y][x];
	return strlen(TEAMS);
}

bool is_dead(t_player_info *player, char **map)
{
	t_vector *pos = player->pos;
	unsigned char enemy[strlen(TEAMS) + 1];

	memset(enemy, 0, strlen(TEAMS));
	enemy[is_enemy(player, map, pos->y, pos->x + 1)]++;
	enemy[is_enemy(player, map, pos->y, pos->x - 1)]++;
	enemy[is_enemy(player, map, pos->y + 1, pos->x)]++;
	enemy[is_enemy(player, map, pos->y - 1, pos->x)]++;
	enemy[is_enemy(player, map, pos->y + 1, pos->x + 1)]++;
	enemy[is_enemy(player, map, pos->y + 1, pos->x - 1)]++;
	enemy[is_enemy(player, map, pos->y - 1, pos->x + 1)]++;
	enemy[is_enemy(player, map, pos->y - 1, pos->x - 1)]++;
	for (unsigned int i = 0; i < strlen(TEAMS); i++) {
		if (enemy[i] >= 2)
			return true;
	}
	return false;
}

bool ended(char **map)
{
	char team = ' ';
	bool found = false;
	bool end = true;

	for (int y = 0; map[y] && y < MAP_SIZE.y; y++) {
		for (int x = 0; x < MAP_SIZE.x; x++) {
			end = (found == true && map[y][x] != team &&
				map[y][x] != ' ' && map[y][x] > 0) ? false :
				end;
			found = (found == false && map[y][x] != team &&
				map[y][x] > 0) ? true : found;
			team = map[y][x] != ' ' && map[y][x] > 0 ? map[y][x] :
				team;
		}
	}
	return (end);
}

int end_game(t_data *data, struct sembuf *sops, int ret)
{
	sops->sem_op = 1;
	semop(data->sem_id, sops, 1);
	return ret;
}

void destroy(t_data *data)
{
	destroy_memory_shared(data);
	destroy_message_queue(data);
	destroy_semaphore(data);
}