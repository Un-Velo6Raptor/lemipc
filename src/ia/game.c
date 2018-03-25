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
#include "config.h"
#include "transmission.h"
#include "ia.h"
#include "end.h"

static int loop_game(t_data *data, struct sembuf *sops, unsigned int index)
{
	static unsigned int i = 0;
	int status;
	static short end = 0;

	// ANNONCE de l'utilisation de la map
	if (data->pos == FIRST)
		printf("\033[3J\033[H\033[2J");
	sops->sem_op = -1;
	semop(data->sem_id, sops, 1);
	if (i > 1 && ended(data->map)) {
		if (end == 5) {
			data->map[data->player->pos->y][data->player->pos->x] = ' ';
			return end_game(data, sops, 0);
		}
		end++;
	} else
		end = 0;
	status = ia(data->player, data->map);
	if (status == -1)
		return end_game(data, sops, 84);
	if (status == 1) {
		printf("You die!\n");
		return end_game(data, sops, 1);
	}
	if (data->pos == FIRST)
		display_tab(data->map);
	if (i == MAX_ACTION_NUMBER) {
		data->map[data->player->pos->y][data->player->pos->x] = ' ';
		return end_game(data, sops, 0);
	}
	if (end_game(data, sops, 0) == 84)
		return 84;
	if (i == 0)
		sleep(1);
	else
		usleep(300000);
	i++;
	return (loop_game(data, sops, index + 1));
}

// This function is the first call, place your player in the map here
int game(t_data *data)
{
	struct sembuf sops; // sem_op=-1: U start ur action, sem_op=1: you end it
	int ret;

	sops.sem_num = 0;
	sops.sem_flg = 0;
	srand(time(NULL));
	data->map = get_the_map(data);
	if (!data->map)
		return 84;
	display_tab(data->map);
	ret = loop_game(data, &sops, 0);
	do {
		if (data->pos == FIRST)
			display_tab(data->map);
		sleep(1);
	} while (ended(data->map) == false);
	if (data->pos == FIRST) {
		destroy_memory_shared(data);
		destroy_message_queue(data);
		destroy_semaphore(data);
	}
	return (ret);
}