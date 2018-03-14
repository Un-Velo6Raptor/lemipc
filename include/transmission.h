/*
** EPITECH PROJECT, 2018
** PSU_lemipc_2017
** File description:
** Created by martin.januario@epitech.eu,
*/

#ifndef PSU_LEMIPC_2017_TRANSMISSION_H
# define PSU_LEMIPC_2017_TRANSMISSION_H

# include <sys/ipc.h>
# include <sys/types.h>
# include "list_enum.h"

typedef struct s_data {
	unsigned int team_number;
	int shm_id;
	enum pos_client pos;
} t_data;


int check_arg(int argc, char **argv);

// Initialize functions
int initialize_memory_shared(t_data *data, key_t key);

#endif //PSU_LEMIPC_2017_TRANSMISSION_H
