/*
** EPITECH PROJECT, 2018
** PSU_lemipc_2017
** File description:
** Created by martin.januario@epitech.eu,
*/

#include <stdlib.h>
#include <sys/msg.h>
#include "transmission.h"

void destroy_message_queue(t_data *data)
{
	msgctl(data->msgq_id, IPC_RMID, NULL);
}