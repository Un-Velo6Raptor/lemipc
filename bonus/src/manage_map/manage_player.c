/*
** EPITECH PROJECT, 2018
** PSU_lemipc_2017
** File description:
** Created by martin.januario@epitech.eu,
*/

#include <unistd.h>
#include "display.h"
#include "config.h"

int tools_manage_player(t_data *data, t_window *sdl_data, SDL_Event *ev)
{
	char tmp[3] = "\0";

	if (sdl_data->tools_used != -1)
		return (0);
	pid_t pid = fork();
	sprintf(tmp, "%d", sdl_data->team_wheel);
	char *arg[4] = {"lemipc", data->path, tmp, 0};

	(void)ev;
	if (pid == 0) {
		check_arg_and_launch(3, arg);
		exit(0);
	}
	return (0);
}