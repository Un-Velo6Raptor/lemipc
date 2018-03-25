/*
** EPITECH PROJECT, 2018
** PSU_lemipc_2017
** File description:
** Created by martin.januario@epitech.eu,
*/

#include "display.h"
#include "config.h"

int tools_manage_reset(t_data *data, t_window *sdl_data, SDL_Event *ev)
{
	(void)sdl_data;
	(void)ev;

	for (int idx_y = 0; data->map[idx_y]; ++idx_y) {
		for (int idx_x = 0; data->map[idx_y][idx_x]; ++idx_x) {
			data->map[idx_y][idx_x] =
				(data->map[idx_y][idx_x] <= -3) ? ' ' :
					data->map[idx_y][idx_x];
		}
	}
	return (0);
}