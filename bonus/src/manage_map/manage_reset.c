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
	char **map = get_the_map(data);

	(void)sdl_data;
	(void)ev;
	if (!map) {
		return (84);
	}
	for (int idx_y = 0; map[idx_y]; ++idx_y) {
		for (int idx_x = 0; map[idx_y][idx_x]; ++idx_x) {
			map[idx_y][idx_x] = (map[idx_y][idx_x] <= -3) ? ' ' :
				map[idx_y][idx_x];
		}
	}
	set_new_map(data, map);
	free_tab(map);
	return (0);
}