/*
** EPITECH PROJECT, 2018
** PSU_lemipc_2017
** File description:
** Created by martin.januario@epitech.eu,
*/

#ifndef PSU_LEMIPC_2017_TRANSMISSION_H
#define PSU_LEMIPC_2017_TRANSMISSION_H

#include <sys/ipc.h>
#include <sys/types.h>
#include <stdbool.h>
#include "list_enum.h"
#include "tools.h"

typedef struct s_msg_data {
	unsigned char team_number;
	long mtype;
	bool is_captain;
	char msg[256];
} t_msg_data;

typedef struct s_player_info {
	bool captain;
	unsigned char team_number;
	t_vector *pos;
	unsigned int ratio;
} t_player_info;

typedef struct s_data {
	int shm_id;
	int sem_id;
	int msgq_id;

	t_player_info *player;

	enum pos_client pos;
} t_data;

// Parsing
int check_arg_and_launch(int argc, char **argv);

// Basics functions
void free_tab(void **tab);
void display_tab(char **tab);

// Initialize functions
int initialize_memory_shared(t_data *data, key_t key, int opt);
int initialize_semaphore(t_data *data, key_t key, int opt);
int initialize_msg_queue(t_data *data, key_t key, int opt);

// Game functions
int game(t_data *data);

// Destroy functions
void destroy_semaphore(t_data *data);
void destroy_message_queue(t_data *data);
void destroy_memory_shared(t_data *data);

// Manage map
char **get_the_map(t_data *data);
int set_new_map(t_data *data, char **map);

// Manage message queue
int send_message(t_data *data, char *str, long mtype);
t_msg_data *read_next_message(t_data *data, long mtype);
t_msg_data *get_next_message_team(t_data *data, long mtpye);
t_msg_data *get_specific_message(t_data *data, long mtype, char *pattern,
	int opt);

#endif //PSU_LEMIPC_2017_TRANSMISSION_H
