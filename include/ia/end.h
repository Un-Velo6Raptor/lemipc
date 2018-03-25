/*
** EPITECH PROJECT, 2018
** PSU_lemipc_2017
** File description:
** Created by sahel.lucas-saoudi@epitech.eu,
*/

#ifndef PSU_LEMIPC_2017_END_H
#define PSU_LEMIPC_2017_END_H

#include <sys/sem.h>
#include "transmission.h"

bool is_dead(t_player_info *player, char **map);
bool ended(char **map);
int end_game(t_data *data, struct sembuf *sops, int ret);

#endif //PSU_LEMIPC_2017_END_H
