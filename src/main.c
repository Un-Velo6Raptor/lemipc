/*
** EPITECH PROJECT, 2018
** PSU_lemipc_2017
** File description:
** Created by martin.januario@epitech.eu,
*/

#include <stdio.h>
#include <string.h>
#include "transmission.h"

static void print_help(void)
{
	fprintf(stderr,
		"USAGE\n\t   ./lemipc PATH TEAM_NUMBER\n\nDESCRIPTION\n");
	fprintf(stderr, "\t   PATH\tpath you’ll give to ftok\n");
	fprintf(stderr, "\t   TEAM_NUMBER\tteam number of the "
		"current champion (greater than 0)\n");
}

static int need_help(int argc, char **argv)
{
	int ret = 0;

	for (int idx = 0; idx < argc; ++idx) {
		if (!strcmp(argv[idx], "--help") || !strcmp(argv[idx], "-h")) {
			print_help();
			ret = 1;
			break;
		}
	}
	return (ret);
}

int main(int argc, char **argv)
{
	int ret = 0;

	if (need_help(argc, argv))
		return (ret);
	if (check_arg(argc, argv))
		ret = 84;
	return (ret);
}