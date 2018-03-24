/*
** EPITECH PROJECT, 2018
** PSU_lemipc_2017
** File description:
** Created by sahel.lucas-saoudi@epitech.eu,
*/

#include "tools.h"

/*
** Characters of teams number
*/
char const * const TEAMS =
	"0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

/*
** Size of the game map
** Allowed size: from 1;1 to 100;100
*/
const t_vector MAP_SIZE = {50, 10};

/*
** Max size of the msg send by process
*/
const unsigned int MSG_SIZE = 256;

/*
** Max number of action of a process
*/
const unsigned int MAX_ACTION_NUMBER = 1000;