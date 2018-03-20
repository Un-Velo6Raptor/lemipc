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

int send_message(t_data *data, char *str, long mtype)
{
	t_msg_data tmp;

	bzero(&tmp, sizeof(t_msg_data));
	tmp.team_number = data->player->team_number;
	// Te permet de savoir lorsque tu reçois un message si il a été transmis par le capitaine. Attention, si le capitaine meurt. Son message reste en temps que capitaine
	tmp.is_captain = data->player->captain;
	tmp.mtype = mtype;
	strncpy(tmp.msg, str, MSG_SIZE);
	msgsnd(data->msgq_id, &tmp, sizeof(t_msg_data), 0);
	return (0);
}

t_msg_data *read_next_message(t_data *data, long mtype)
{
	t_msg_data *msg = malloc(sizeof(t_msg_data) * 1);

	if (!msg) {
		fprintf(stderr, "Error: Malloc failed\n");
		return (NULL);
	}
	// Attention, si pas de message ou pas de message avec ce mtype. Il va wait un message
	msgrcv(data->msgq_id, msg, sizeof(t_msg_data), mtype, 0);
	return (msg);
}

// Infinite loop while she get the team message, take care
// U can get the message send by the same client, take care too
t_msg_data *get_next_message_team(t_data *data, long mtpye)
{
	t_msg_data *tmp = read_next_message(data, mtpye);
	t_data msg_return;

	if (!tmp)
		return (NULL);
	else if (tmp->team_number == data->player->team_number)
		return (tmp);
	msg_return.player = malloc(sizeof(t_player_info));
	if (!msg_return.player)
		return NULL;
	msg_return.player->team_number = tmp->team_number;
	msg_return.player->captain = tmp->is_captain;
	send_message(&msg_return, tmp->msg, mtpye);
	free(msg_return.player);
	free(tmp);
	return (get_next_message_team(data, mtpye));
}

// opt=1 : check for the specific message in the team. opt=0 : search for the specific message in every team
// Infinite loop while she get the specific message, take care
// U can get the message send by the same client, take care too
t_msg_data *get_specific_message(t_data *data, long mtype, char *pattern,
	int opt
)
{
	t_msg_data *tmp = (!opt) ? read_next_message(data, mtype) :
		get_next_message_team(data, mtype);
	t_data msg_return;

	if (!tmp)
		return (NULL);
	else if (!strncasecmp(tmp->msg, pattern, strlen(pattern)))
		return (tmp);
	msg_return.player = malloc(sizeof(t_player_info));
	if (!msg_return.player)
		return NULL;
	msg_return.player->team_number = tmp->team_number;
	msg_return.player->captain = tmp->is_captain;
	send_message(&msg_return, tmp->msg, mtype);
	free(msg_return.player);
	free(tmp);
	return (get_specific_message(data, mtype, pattern, opt));
}

void destroy_message_queue(t_data *data)
{
	msgctl(data->msgq_id, IPC_RMID, NULL);
}