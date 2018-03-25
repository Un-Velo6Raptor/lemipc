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
	t_vector size = get_block_size();
	t_vector index = {-1, -1};

	(void)sdl_data;
	index.x = (ev->button.x - MSG_WIDTH) / size.x;
	index.y = ev->button.y / size.y;
	if (index.x < 0 || index.x >= MAP_SIZE.x || index.y < 0 ||
		index.y >= MAP_SIZE.y)
		return (0);
	if (data->map[index.y][index.x] == ' ') {
		data->map[index.y][index.x] = WALL_CHAR;
	}
	return (0);
}