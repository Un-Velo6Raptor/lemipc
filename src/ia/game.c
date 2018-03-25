/*
** EPITECH PROJECT, 2018
** PSU_lemipc_2017
** File description:
** Created by martin.januario@epitech.eu,
*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/sem.h>
#include <strings.h>
#include <string.h>
#include "config.h"
#include "transmission.h"
#include "ia.h"
#include "end.h"
#include "placement.h"

static int start_ai(t_data *data, struct sembuf *sops, unsigned int *act)
{
	int status = ia(data);

	if (*act == MAX_ACTION_NUMBER)
		return end_game(data, sops, 1);
	if (*act)
		read_next_message(data, TIDX(data->player->team_number),
			IPC_NOWAIT);
	if (status == 1) {
		printf("You die\n");
		send_message(data, "die", TIDX(data->player->team_number));
	} else if (!status) {
		placement(data->map, data->player);
		if (data->pos == FIRST)
			display_tab(data->map);
	}
	(*act)++;
	return end_game(data, sops, status);
}

static int loop_game(t_data *data, struct sembuf *sops)
{
	static unsigned int i = 0;
	int status;
	static unsigned int end = 0;
	char str[12];

	sops->sem_op = -1;
	semop(data->sem_id, sops, 1);
	end = i > 1 && ended(data->map) ? end + 1 : 0;
	if (end == 5) {
		send_message(data, "end", strlen(TEAMS) + 2);
		data->map[data->player->pos->y][data->player->pos->x] = ' ';
		return end_game(data, sops, 0);
	}
	status = start_ai(data, sops, &i);
	if (status)
		return status == 84 ? status : 0;
	sprintf(str, "%02i;%02i", data->player->pos->x, data->player->pos->y);
	send_message(data, str, TIDX(data->player->team_number));
	usleep((i == 0) ? 1000000 : 300000);
	return (loop_game(data, sops));
}

static void wait_end_game(t_data *data)
{
	if (data->pos != FIRST) {
		read_next_message(data, strlen(TEAMS) + 2, 0);
		send_message(data, "end", strlen(TEAMS) + 2);
	} else {
		while (ended(data->map) == false) {
			display_tab(data->map);
			sleep(1);
		}
		sleep(10);
		destroy(data);
	}
}

// This function is the first call, place your player in the map here
int game(t_data *data)
{
	struct sembuf sops;
	int ret;

	sops.sem_num = 0;
	sops.sem_flg = 0;
	srand(time(NULL));
	data->map = get_the_map(data);
	if (!data->map)
		return 84;
	ret = loop_game(data, &sops);
	wait_end_game(data);
	free(data->map);
	return (ret);
}