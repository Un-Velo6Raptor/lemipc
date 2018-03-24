/*
** EPITECH PROJECT, 2018
** PSU_lemipc_2017
** File description:
** Created by martin.januario@epitech.eu,
*/

#include <stdio.h>
#include <stdlib.h>
#include "transmission.h"

void free_tab(void **tab)
{
	for (int idx = 0; tab && tab[idx]; ++idx) {
		free(tab[idx]);
	}
	if (tab)
		free(tab);
}

void display_tab(char **tab)
{
	printf("-- START TAB --\n");
	for (int idx = 0; tab && tab[idx]; ++idx) {
		printf("%d: [%s]\n", idx, tab[idx]);
	}
	printf("-- END TAB --\n");
}