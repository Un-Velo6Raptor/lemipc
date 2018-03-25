/*
** EPITECH PROJECT, 2018
** PSU_lemipc_2017
** File description:
** Created by martin.januario@epitech.eu,
*/

#include "display.h"
#include "config.h"

int tools_manage_rubber(t_data *data, t_window *sdl_data, SDL_Event *ev)
{
	t_vector size = get_block_size();
	t_vector index = {-1, -1};

	(void)sdl_data;
	index.x = (ev->button.x - MSG_WIDTH) / size.x;
	index.y = ev->button.y / size.y;
	if (index.x < 0 || index.x >= MAP_SIZE.x || index.y < 0 ||
		index.y >= MAP_SIZE.y)
		return (0);

	if (data->map[index.y][index.x] <= -3) {
		data->map[index.y][index.x] = ' ';
	}
	return (0);
}