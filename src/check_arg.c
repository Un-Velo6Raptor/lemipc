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

static int take_team_number(t_data *data, char *str)
{
	int ret = 0;
	unsigned int idx = 0;

	data->team_number = 0;
	for (; str[idx] != '\0' && str[idx] >= '0' && str[idx] <= '9'; ++idx);
	if (idx && strlen(str) == idx) {
		data->team_number = (unsigned int)atoi(str);
	}
	if (!data->team_number) {
		fprintf(stderr, "Error: TEAM_NUMBER must be "
			"a valid and positiv number\n");
		ret = 84;
	}
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
			ret = initialize_memory_shared(data, key);
			ret += initialize_semaphore(data, key);
			ret += initialize_msg_queue(data, key);
		} else {
			ret = 84;
			fprintf(stderr, "Error: Can't create the key\n");
		}
	}

	return ((!ret) ? 0 : 84);
}

int check_arg(int argc, char **argv)
{
	int ret = 0;
	t_data data;

	if (argc != 3) {
		fprintf(stderr, "Error: We need 3 arguments, look --help\n");
		ret = 84;
	} else {
		if (take_team_number(&data, argv[2]))
			ret = 84;
		else if (take_path(&data, argv[1]))
			ret = 84;
	}
	return ((ret != 84) ? game(&data) : ret);
}