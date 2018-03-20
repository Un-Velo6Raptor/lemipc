/*
** EPITECH PROJECT, 2018
** PSU_lemipc_2017
** File description:
** Created by martin.januario@epitech.eu,
*/

#include <sys/sem.h>
#include "transmission.h"

void destroy_semaphore(t_data *data)
{
	semget(data->sem_id, 1, IPC_RMID);
}