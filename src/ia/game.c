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
#include <strings.h>
#include <string.h>
#include "config.h"
#include "transmission.h"
#include "ia.h"
#include "end.h"
#include "placement.h"

static int loop_game(t_data *data, struct sembuf *sops)
{
	static unsigned int i = 0;
	int status;
	static short end = 0;

	if (data->pos == FIRST)
		printf("\033[3J\033[H\033[2J");
	sops->sem_op = -1;
	semop(data->sem_id, sops, 1);
	if (i > 1 && ended(data->map)) {
		if (end == 5) {
			send_message(data, "end", strlen(TEAMS) + 2);
			send_message(data, "end", strlen(TEAMS) + 3);
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
		send_message(data, "die", TEAMS - index(TEAMS, data->player->team_number) + 1);
		char *s = malloc(20);
		sprintf(s, "%c: I die :'(", data->player->team_number);
		send_message(data, s, strlen(TEAMS) + 3);
		return end_game(data, sops, 1);
	}
	placement(data->map, data->player);
	if (data->pos == FIRST)
		display_tab(data->map);
	if (i == MAX_ACTION_NUMBER)
		return end_game(data, sops, 0);
	if (end_game(data, sops, 0) == 84)
		return 84;
	char *str = malloc(12);
	sprintf(str, "team %c: I go in %i;%i", data->player->team_number, data->player->pos->x, data->player->pos->y);
	send_message(data, str, TEAMS - index(TEAMS, data->player->team_number) + 1);
	send_message(data, str, strlen(TEAMS) + 3);
	usleep((i == 0) ? 1000000 : 300000);
	i++;
	return (loop_game(data, sops));
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
	if (data->pos != FIRST)
		read_next_message(data, strlen(TEAMS) + 2);
	else {
		while (ended(data->map) == false) {
			printf("\033[3J\033[H\033[2J");
			display_tab(data->map);
			sleep(1);
		}
		sleep(10);
		destroy(data);
	}
	free(data->map);
	return (ret);
}