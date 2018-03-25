/*
** EPITECH PROJECT, 2018
** PSU_lemipc_2017
** File description:
** Created by martin.januario@epitech.eu,
*/

#include <unistd.h>
#include "display.h"
#include "config.h"

static const char WALL_WATER = -5;

static void put_water_here(char **map, t_vector *index, int x, int y)
{
	if (index->x + x < 0 || index->y + y < 0 || !map[index->y + y] ||
		!map[index->y + y][index->x + x])
		return;
	if (map[index->y + y][index->x + x] == ' ')
		map[index->y + y][index->x + x] = WALL_WATER;
}

static int water_bucket_fall(char **map, t_vector *index)
{
	int ret = 0;

	for (int idx = -1; idx < 2; ++idx) {
		for (int idx_x = -1; idx_x < 2; ++idx_x) {
			if (!(rand() % 2))
				put_water_here(map, index, idx_x, idx);
		}
	}
	return (ret);
}

int tools_manage_water(t_data *data, t_window *sdl_data, SDL_Event *ev)
{
	t_vector size = get_block_size();
	t_vector index = {-1, -1};

	(void)sdl_data;
	index.x = (ev->button.x - MSG_WIDTH) / size.x;
	index.y = ev->button.y / size.y;
	water_bucket_fall(data->map, &index);
	return (0);
}