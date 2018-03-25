/*
** EPITECH PROJECT, 2018
** PSU_lemipc_2017
** File description:
** Created by martin.januario@epitech.eu,
*/

#include "display.h"

int get_limit_x(int x)
{
	return (MSG_WIDTH + (x * MAP_SIZE.x));
}

int get_limit_y(int y)
{
	return (y * MAP_SIZE.y);
}