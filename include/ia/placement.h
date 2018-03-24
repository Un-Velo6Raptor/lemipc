/*
** EPITECH PROJECT, 2018
** PSU_lemipc_2017
** File description:
** Created by sahel.lucas-saoudi@epitech.eu,
*/

#ifndef PSU_LEMIPC_2017_PLACEMENT_H
#define PSU_LEMIPC_2017_PLACEMENT_H

#include "tools.h"

t_vector *player_drop(char **map, unsigned char team);
void move_to_target(t_player_info *player, short **distance_map, t_vector *pos);
void placement(char **map, t_player_info *player);

#endif //PSU_LEMIPC_2017_PLACEMENT_H
