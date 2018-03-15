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

const unsigned int HEIGHT_MAP = 10;
const unsigned int LENGTH_MAP = 10;

static int create_memory_shared(t_data *data, key_t key)
{
	char *str = malloc(sizeof(char) * (HEIGHT_MAP * LENGTH_MAP + 1));
	void *addr;

	if (!str)
		return (84);
	str = memset(str, ' ', 100);
	str[100] = '\0';
	data->shm_id = shmget(key, (HEIGHT_MAP * LENGTH_MAP),
		IPC_CREAT | SHM_R | SHM_W);
	data->pos = FIRST;
	if (data->shm_id == -1)
		return (84);
	addr = shmat(data->shm_id, NULL, SHM_R | SHM_W);
	sprintf((char *)addr, str);
	free(str);
	return (0);
}

int initialize_memory_shared(t_data *data, key_t key)
{
	int ret = 0;

	data->pos = UNKNOWN;
	data->player.captain = 0;
	data->player.ratio = 0;
	data->player.x = 0;
	data->player.y = 0;
	data->shm_id = shmget(key, (HEIGHT_MAP * LENGTH_MAP), SHM_R | SHM_W);
	if (data->shm_id == -1)
		ret = create_memory_shared(data, key);
	return (ret);
}