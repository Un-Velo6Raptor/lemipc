/*
** EPITECH PROJECT, 2018
** PSU_lemipc_2017
** File description:
** Created by martin.januario@epitech.eu,
*/

#include "display.h"
#include "config.h"

static const char WALL_CHAR = -3;

int tools_manage_wall(t_data *data, t_window *sdl_data, SDL_Event *ev)
{
	char **map = get_the_map(data);
	t_vector size = get_block_size();
	t_vector index = {-1, -1};

	(void)sdl_data;
	if (!map) {
		return (84);
	}
	index.x = (ev->button.x - MSG_WIDTH) / size.x;
	index.y = ev->button.y / size.y;
	if (map[index.y][index.x] == ' ') {
		map[index.y][index.x] = WALL_CHAR;
		set_new_map(data, map);
	}
	free_tab((void **) map);
	return (0);
}