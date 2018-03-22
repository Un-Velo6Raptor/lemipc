/*
** EPITECH PROJECT, 2018
** PSU_lemipc_2017
** File description:
** Created by martin.januario@epitech.eu,
*/

#include <stdio.h> // TODO: deleted it
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/sem.h>
#include <time.h>
#include <config.h>
#include "transmission.h"
#include "ia.h"

static int loop_game(t_data *data, struct sembuf *sops, unsigned int index)
{
	static int i = 0;

	// ANNONCE de l'utilisation de la map
	printf("-- WAIT\n");
	sops->sem_op = -1;
	semop(data->sem_id, sops, 1);
	printf("-- EXEC\n");

	char **tmp = get_the_map(data);
	if (!tmp) {
		sops->sem_op = 1;
		semop(data->sem_id, sops, 1);
		return 84;
	}
	int status = ia(data->player, tmp);
	if (status == -1) {
		sops->sem_op = 1;
		semop(data->sem_id, sops, 1);
		return 84;
	}
	if (status == 1) {
		set_new_map(data, tmp);
		sops->sem_op = 1;
		semop(data->sem_id, sops, 1);
		printf("You die!\n");
		return 0;
	}
	printf("-- AFTER --\n");
	display_tab(tmp);
	usleep(300000);
	if (i == MAX_ACTION_NUMBER) // todo delete
		tmp[data->player->pos->y][data->player->pos->x] = ' ';
	if (set_new_map(data, tmp) == 84) {
		sops->sem_op = 1;
		semop(data->sem_id, sops, 1);
		return 84;
	}
	free_tab(tmp);

	// ANNONCE de la "libération" de la map
	sops->sem_op = 1;
	semop(data->sem_id, sops, 1);

	if (i == MAX_ACTION_NUMBER)
		return 0; // TODO delete;
	i++;
	return (loop_game(data, sops, index + 1));
}

// This function is the first call, place your player in the map here
int game(t_data *data)
{
	struct sembuf sops; // sem_op=-1: U start ur action, sem_op=1: you end it
	int ret;

	printf("SEM_ID: %d\n", data->sem_id);
	sops.sem_num = 0;
	sops.sem_flg = 0;
	srand(time(NULL));
	ret = loop_game(data, &sops, 0);
	destroy_memory_shared(data);
	destroy_message_queue(data);
	destroy_semaphore(data);
	return (ret);
}