/*
** EPITECH PROJECT, 2018
** PSU_lemipc_2017
** File description:
** Created by martin.januario@epitech.eu,
*/

#include <sys/shm.h>
#include <stdlib.h>
#include "transmission.h"
#include "config.h"

char **get_the_map(t_data *data)
{
	char **map = malloc(sizeof(char [MAP_SIZE.y + 1][MAP_SIZE.x + 1]));
	char *str = shmat(data->shm_id, NULL, SHM_R | SHM_W);
	int y = 0;

	if (!map || str == (void *) -1)
		return NULL;
	for (; y < MAP_SIZE.y; y++) {
		map[y] = str;
		str += MAP_SIZE.x + 1;
	}
	map[y] = NULL;
	return map;
}

void destroy_memory_shared(t_data *data)
{
	shmctl(data->shm_id, IPC_RMID, NULL);
}