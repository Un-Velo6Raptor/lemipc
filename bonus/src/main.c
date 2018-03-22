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
		"USAGE\n\t   ./ipc_map PATH\n\nDESCRIPTION\n");
	fprintf(stderr, "\t    PATH\tpath you’ll give to ftok\n");
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
	if (check_arg_and_launch(argc, argv))
		ret = 84;
	return (ret);
}