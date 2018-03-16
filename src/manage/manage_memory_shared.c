/*
** EPITECH PROJECT, 2018
** PSU_lemipc_2017
** File description:
** Created by martin.januario@epitech.eu,
*/

#include <stdio.h>
#include <string.h>
#include <sys/shm.h>
#include <stdlib.h>
#include "transmission.h"

extern const unsigned int HEIGHT_MAP;

extern const unsigned int LENGTH_MAP;

int set_new_map(t_data *data, char **map)
{
	char *string_map = malloc(sizeof(char) * (HEIGHT_MAP * LENGTH_MAP + 1));
	void *addr;

	if (!string_map) {
		fprintf(stderr, "Error: Malloc failed\n");
		return (84);
	}
	string_map[0] = '\0';
	for (int idx = 0; map && map[idx]; ++idx) {
		strcat(string_map, map[idx]);
	}
	addr = shmat(data->shm_id, NULL, SHM_R | SHM_W);
	sprintf((char *)addr, "%s", string_map);
	return (0);
}

char **get_the_map(t_data *data)
{
	char **result = malloc(sizeof(char *) * (HEIGHT_MAP + 1));
	void *string_map;
	unsigned int idx = 0;

	if (!result) {
		fprintf(stderr, "Error: Malloc failed\n");
		return (NULL);
	}
	string_map = shmat(data->shm_id, NULL, SHM_R | SHM_W);
	for (; idx < HEIGHT_MAP; ++idx) {
		result[idx] = strndup(&((char *)string_map)[LENGTH_MAP * idx],
			LENGTH_MAP);
	}
	result[idx] = NULL;
	return (result);
}

void destroy_memory_shared(t_data *data)
{
	shmctl(data->shm_id, IPC_RMID, NULL);
}