/*
** EPITECH PROJECT, 2018
** PSU_lemipc_2017
** File description:
** Created by martin.januario@epitech.eu,
*/

#include "config.h"
#include "display.h"

t_vector get_block_size(void)
{
	t_vector result;

	if (MAP_SIZE.x > 0 && MAP_SIZE.y > 0) {
		result.x = (WINDOW_WIDTH - MSG_WIDTH) / MAP_SIZE.x;
		result.y = (WINDOW_HEIGHT - TOOLS_HEIGHT) / MAP_SIZE.y;
	} else {
		result.x = -1;
		result.y = -1;
	}
	return (result);
}

static void draw_grid(t_window *sdl_map, t_vector *block_size)
{
	SDL_SetRenderDrawColor(sdl_map->renderer, 0, 0, 0, 255);
	int idx_height = 0;
	int idx_width = MSG_WIDTH;

	for (; idx_height + block_size->y <=
		WINDOW_HEIGHT - TOOLS_HEIGHT; idx_height += block_size->y)
		SDL_RenderDrawLine(sdl_map->renderer, MSG_WIDTH, idx_height,
			WINDOW_WIDTH, idx_height);
	for (; idx_width + block_size->x <= WINDOW_WIDTH; idx_width += block_size->x)
		SDL_RenderDrawLine(sdl_map->renderer, idx_width, 0, idx_width,
			WINDOW_HEIGHT - TOOLS_HEIGHT);
	SDL_Rect tmp;
	SDL_SetRenderDrawColor(sdl_map->renderer, 0, 0, 0, 255);
	if (idx_height < WINDOW_HEIGHT - TOOLS_HEIGHT) {
		tmp.x = MSG_WIDTH;
		tmp.y = idx_height;
		tmp.w = WINDOW_WIDTH - MSG_WIDTH;
		tmp.h = idx_height;
		SDL_RenderFillRect(sdl_map->renderer, &tmp);
	}
	if (idx_width < WINDOW_WIDTH) {
		tmp.x = idx_width;
		tmp.y = 0;
		tmp.w = idx_width;
		tmp.h = WINDOW_HEIGHT - TOOLS_HEIGHT;
		SDL_RenderFillRect(sdl_map->renderer, &tmp);
	}
}

static int check_new_color(t_window *sdl_map, char player)
{
	if (player <= 0 || player == ' ')
		return (0);
	while (sdl_map->list_team && sdl_map->list_team->next &&
		sdl_map->list_team->representation != player)
		sdl_map->list_team = sdl_map->list_team->next;
	if (sdl_map->list_team && sdl_map->list_team->representation == player)
		return (0);
	t_team *new_team = malloc(sizeof(t_team) * 1);
	if (!new_team)
		return (84);
	new_team->next = NULL;
	new_team->r = rand() % 220;
	new_team->g = rand() % 220;
	new_team->b = rand() % 220;
	new_team->representation = player;
	if (!sdl_map->list_team)
		sdl_map->list_team = new_team;
	else
		sdl_map->list_team->next = new_team;
	return (0);
}

static int check_new_team(t_window *sdl_map, char **map)
{
	t_team *header = sdl_map->list_team;
	int ret = 0;

	for (int idx_y = 0; !ret && map && map[idx_y]; ++idx_y) {
		for (int idx_x = 0;
			!ret && map[idx_y][idx_x] != '\0'; ++idx_x) {
			ret = check_new_color(sdl_map, map[idx_y][idx_x]);
		}
		if (!header)
			header = sdl_map->list_team;
		sdl_map->list_team = header;
	}
	return (ret);
}

int draw_map_sdl(t_window *sdl_map, char **map)
{
	t_vector block_size = get_block_size();
	int ret = 0;

	draw_grid(sdl_map, &block_size);
	ret = check_new_team(sdl_map, map);
	if (!ret) {
		draw_player(sdl_map, &block_size, map);
	}
	return (ret);
}