/*
** EPITECH PROJECT, 2018
** PSU_lemipc_2017
** File description:
** Created by martin.januario@epitech.eu,
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "transmission.h"
#include "display.h"

static int initialize_ipc(t_data *data, key_t key)
{
	int ret = 0;
	ret = initialize_memory_shared(data, key, 1);
	ret += initialize_semaphore(data, key, 1);
	ret += initialize_msg_queue(data, key, 1);
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
		data->path = strdup(str);
		key = ftok(str, 0);
		if (key != -1) {
			ret = initialize_ipc(data, key);
		} else {
			ret = 84;
			fprintf(stderr, "Error: Can't create the key\n");
		}
	}
	return (ret ? 84 : 0);
}

int check_arg_and_launch_display(int argc, char **argv)
{
	t_data data;

	if (argc != 2) {
		fprintf(stderr, "Error: We need 2 arguments, look --help\n");
		return 84;
	} else {
		data.player = malloc(sizeof(t_player_info));
		if (!data.player)
			return 84;
		data.player->pos = malloc(sizeof(t_vector));
		if (!data.player->pos)
			return 84;
	}
	if (take_path(&data, argv[1]))
		return 84;
	return (graphical_display(&data));
}