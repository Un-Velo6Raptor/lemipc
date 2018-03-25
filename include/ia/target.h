/*
** EPITECH PROJECT, 2018
** PSU_lemipc_2017
** File description:
** Created by sahel.lucas-saoudi@epitech.eu,
*/

#ifndef PSU_LEMIPC_2017_TARGET_H
#define PSU_LEMIPC_2017_TARGET_H

#include "transmission.h"
#include "tools.h"

t_vector *select_target(t_player_info *player, char **map, int **distance_map);
unsigned int get_distance(t_player_info *player, t_vector *pos);
int get_distance_at(int **map, int y, int x);
int **get_distance_map(t_player_info *player, char **map);

#endif //PSU_LEMIPC_2017_TARGET_H
