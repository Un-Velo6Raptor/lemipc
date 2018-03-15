/*
** EPITECH PROJECT, 2018
** PSU_lemipc_2017
** File description:
** Created by martin.januario@epitech.eu,
*/

#include "sys/shm.h"
#include <sys/sem.h>
#include <stdio.h>
#include "transmission.h"

static int create_semaphore(t_data *data, key_t key)
{
	int ret = 0;

	data->sem_id = semget(key, 1, IPC_CREAT | SHM_R | SHM_W);
	if (data->sem_id == -1)
		ret = 84;
	else
		semctl(data->sem_id, 0, SETVAL, 1);
	return (ret);
}

int initialize_semaphore(t_data *data, key_t key)
{
	int ret = 0;

	data->sem_id = semget(key, 1, SHM_R | SHM_W);
	if (data->sem_id == -1)
		ret = create_semaphore(data, key);
	return (ret);
}