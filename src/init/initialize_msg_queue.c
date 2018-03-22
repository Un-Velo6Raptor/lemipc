/*
** EPITECH PROJECT, 2018
** PSU_lemipc_2017
** File description:
** Created by martin.januario@epitech.eu,
*/

#include <stdio.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include "transmission.h"

static int create_message_queue(t_data *data, key_t key)
{
	int ret = 0;

	data->player->captain = true;
	data->msgq_id = msgget(key, IPC_CREAT | SHM_R | SHM_W);
	if (data->msgq_id == -1)
		ret = 84;
	return (ret);
}

int initialize_msg_queue(t_data *data, key_t key, int opt)
{
	int ret = 0;

	data->msgq_id = msgget(key, SHM_R | SHM_W);
	if (data->msgq_id == -1 && opt)
		ret = create_message_queue(data, key);
	else if (data->msgq_id == -1) {
		fprintf(stderr, "Error: Message queue not set\n");
		ret = 84;
	}
	return (ret);
}