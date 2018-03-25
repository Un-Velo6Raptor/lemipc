/*
** EPITECH PROJECT, 2018
** PSU_lemipc_2017
** File description:
** Created by martin.januario@epitech.eu,
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <string.h>
#include "transmission.h"
#include "config.h"

int send_message(t_data *data, const char *str, long mtype)
{
	t_msg_data tmp;

	bzero(&tmp, sizeof(t_msg_data));
	tmp.mtype = mtype;
	strncpy(tmp.mtext, str, MSG_SIZE);
	msgsnd(data->msgq_id, &tmp, MSG_SIZE, IPC_NOWAIT);
	return (0);
}

t_msg_data *read_next_message(t_data *data, long mtype, int flag)
{
	t_msg_data *msg = malloc(sizeof(t_msg_data) * 1);

	if (!msg) {
		fprintf(stderr, "Error: Malloc failed\n");
		return (NULL);
	}
	msg->mtype = mtype;
	msgrcv(data->msgq_id, msg, MSG_SIZE, mtype, flag);
	return (msg);
}

// opt = 1 : check for the specific message in the team. opt = 0 :
// search for the specific message in every team
// Infinite loop while she get the specific message, take care
// U can get the message send by the same client, take care too
t_msg_data *get_specific_message(t_data *data, long mtype, char *pattern,
	int opt
)
{
	t_msg_data *tmp = read_next_message(data, mtype, 0);
	t_data msg_return;

	if (!tmp)
		return (NULL);
	else if (!strncasecmp(tmp->mtext, pattern, strlen(pattern)))
		return (tmp);
	msg_return.player = malloc(sizeof(t_player_info));
	if (!msg_return.player)
		return NULL;
	send_message(&msg_return, tmp->mtext, mtype);
	free(msg_return.player);
	free(tmp);
	return (get_specific_message(data, mtype, pattern, opt));
}

void destroy_message_queue(t_data *data)
{
	msgctl(data->msgq_id, IPC_RMID, NULL);
}