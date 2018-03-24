/*
** EPITECH PROJECT, 2018
** PSU_lemipc_2017
** File description:
** Created by martin.januario@epitech.eu,
*/

#include "display.h"
#include "config.h"

static const char WALL_LEAF = -4;

static int put_a_tree_here(char **map, t_vector *index)
{
	int ret = 84;

	if (map[index->y][index->x] == ' ') {
		map[index->y][index->x] = WALL_LEAF;
		if (index->x > 0 && map[index->y][index->x - 1] == ' ')
			map[index->y][index->x - 1] = WALL_LEAF;
		if (map[index->y][index->x + 1] == ' ')
			map[index->y][index->x + 1] = WALL_LEAF;
		if (map[index->y + 1] && map[index->y + 1][index->x] == ' ')
			map[index->y + 1][index->x] = WALL_LEAF;
		if (index->y > 0 && map[index->y - 1][index->x] == ' ')
			map[index->y - 1][index->x] = WALL_LEAF;
		ret = 0;
	}

	return (ret);
}

int tools_manage_leaf(t_data *data, t_window *sdl_data, SDL_Event *ev)
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
	if (!put_a_tree_here(map, &index))
		set_new_map(data, map);
	free_tab(map);
	return (0);
}