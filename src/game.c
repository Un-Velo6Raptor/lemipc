/*
** EPITECH PROJECT, 2018
** PSU_lemipc_2017
** File description:
** Created by martin.januario@epitech.eu,
*/

#include <stdio.h> // TODO: deleted it

#include <unistd.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include "transmission.h"

static int loop_game(t_data *data, struct sembuf *sops)
{
	// ANNONCE de l'utilisation de la map
	sops->sem_op = -1;
	semop(data->sem_id, sops, 1);

	char **tmp = get_the_map(data);
	if (!tmp)
		return (84);

	display_tab(tmp);
	sleep(5);
	tmp[0][1] = 'X';
	if (set_new_map(data, tmp) == 84)
		return (84);
	free_tab(tmp);

	// ANNONCE de la "libération" de la map
	sops->sem_op = 1;
	semop(data->sem_id, sops, 1);

	return (loop_game(data, sops));
}

// This function is the first call, place your player in the map here
int game(t_data *data)
{
	struct sembuf sops; // -1: U start ur action, 1: you end it

	printf("SEM_ID: %d\n", data->sem_id);
	sops.sem_num = 0;
	sops.sem_flg = 0;
	return (loop_game(data, &sops));
}