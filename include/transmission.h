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

typedef struct player_info {
	int captain;
	int x;
	int y;
	int ratio;
} t_player_info;

typedef struct s_data {
	unsigned int team_number;

	int shm_id;
	int sem_id;
	int msgq_id;

	t_player_info player;

	enum pos_client pos;
} t_data;

// Parsing
int check_arg(int argc, char **argv);

// Basics functions
void free_tab(char **tab);
void display_tab(char **tab);

// Initialize functions
int initialize_memory_shared(t_data *data, key_t key);
int initialize_semaphore(t_data *data, key_t key);
int initialize_msg_queue(t_data *data, key_t key);

// Game functions
int game(t_data *data);

// Manage functions
void destroy_semaphore(t_data *data);
void destroy_message_gueue(t_data *data);
void destroy_memory_shared(t_data *data);
char **get_the_map(t_data *data);
int set_new_map(t_data *data, char **map);

#endif //PSU_LEMIPC_2017_TRANSMISSION_H
