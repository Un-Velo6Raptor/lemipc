/*
** EPITECH PROJECT, 2018
** PSU_lemipc_2017
** File description:
** Created by martin.januario@epitech.eu,
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "transmission.h"
#include "config.h"

static int take_team_number(t_data *data, char *str)
{
	int ret = 0;
	unsigned int idx = 0;

	data->player->team_number = 0;
	for (; str[idx] && str[idx] >= '0' && str[idx] <= '9'; ++idx);
	if (idx && strlen(str) == idx) {
		data->player->team_number = (unsigned char)atoi(str);
	}
	if (data->player->team_number >= strlen(TEAMS)) {
		fprintf(stderr, "%s\n", str);
		fprintf(stderr, "Error: TEAM_NUMBER must be "
			"between 0 and %lu\n", strlen(TEAMS));
		ret = 84;
	} else
		data->player->team_number =
			(unsigned char) TEAMS[data->player->team_number];
	return (ret);
}

static int take_path(t_data *data, char *str)
{
	int ret = 0;
	key_t key;

	if (!strlen(str)) {
		fprintf(stderr, "Error: PATH must be valid\n");
		ret = 84;
	} else {
		key = ftok(str, 0);
		if (key != -1) {
			ret = initialize_memory_shared(data, key, 1);
			ret += initialize_semaphore(data, key, 1);
			ret += initialize_msg_queue(data, key, 1);
		} else {
			ret = 84;
			fprintf(stderr, "Error: Can't create the key\n");
		}
	}
	return (ret ? 84 : 0);
}

int check_arg_and_launch(int argc, char **argv)
{
	t_data data;

	if (argc != 3) {
		fprintf(stderr, "Error: We need 3 arguments, look --help\n");
		return 84;
	} else {
		data.player = malloc(sizeof(t_player_info));
		if (!data.player)
			return 84;
		data.player->pos = malloc(sizeof(t_vector));
		if (!data.player->pos)
			return 84;
		if (take_team_number(&data, argv[2]))
			return 84;
		else if (take_path(&data, argv[1]))
			return 84;
	}
	return (game(&data));
}