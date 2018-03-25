/*
** EPITECH PROJECT, 2018
** PSU_lemipc_2017
** File description:
** Created by martin.januario@epitech.eu,
*/

#include <stdio.h>
#include <stdlib.h>
#include <config.h>
#include "transmission.h"

void free_tab(void **tab)
{
	for (int idx = 0; tab && idx < MAP_SIZE.y; ++idx) {
		free(tab[idx]);
	}
	if (tab)
		free(tab);
}

void display_tab(char **tab)
{
	printf("\033[3J\033[H\033[2J");
	for (int idx = 0; tab && idx < MAP_SIZE.y; ++idx) {
		printf("%02d: [%s]\n", idx, tab[idx]);
	}
}