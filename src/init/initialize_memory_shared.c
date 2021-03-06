/*
** EPITECH PROJECT, 2018
** PSU_lemipc_2017
** File description:
** Created by martin.januario@epitech.eu,
*/

#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <stdio.h>
#include "transmission.h"
#include "config.h"

static int create_memory_shared(t_data *data, key_t key)
{
	char *map;

	data->shm_id = shmget(key,
		(unsigned int)((MAP_SIZE.x + 1) * MAP_SIZE.y),
		IPC_CREAT | SHM_R | SHM_W);
	data->pos = FIRST;
	if (data->shm_id == -1)
		return (84);
	map = shmat(data->shm_id, NULL, SHM_R | SHM_W);
	memset(map, ' ', (MAP_SIZE.x + 1) * MAP_SIZE.y);
	for (int i = MAP_SIZE.x;
		i < MAP_SIZE.y * (MAP_SIZE.x + 1); i += MAP_SIZE.x + 1) {
		map[i] = '\0';
	}

	return (0);
}

int initialize_memory_shared(t_data *data, key_t key, int opt)
{
	int ret = 0;

	data->pos = UNKNOWN;
	data->player->captain = false;
	data->player->ratio = 0;
	data->player->pos->x = -1;
	data->player->pos->y = -1;
	data->shm_id = shmget(key,
		(unsigned int)((MAP_SIZE.x + 1) * MAP_SIZE.y), SHM_R | SHM_W);
	if (data->shm_id == -1 && opt) {
		ret = create_memory_shared(data, key);
	} else if (data->shm_id == -1) {
		fprintf(stderr, "Error: Memory Shared not set\n");
		ret = 84;
	}
	return (ret);
}