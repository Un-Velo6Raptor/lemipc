/*
** EPITECH PROJECT, 2018
** PSU_lemipc_2017
** File description:
** Created by martin.januario@epitech.eu,
*/

#include "config.h"
#include "display.h"

static SDL_Rect get_block_to_color(t_vector *idx, t_vector *block_size)
{
	SDL_Rect block;

	block.x = MSG_WIDTH + (idx->x * block_size->x) + 1;
	block.w = block_size->x - 1;

	block.y = (idx->y * block_size->y) + 1;
	block.h = block_size->y - 1;
	return (block);
}

static void fill_rect_player(t_window *sdl_data, t_vector *block_size,
	t_team *player, t_vector *idx
)
{
	SDL_Rect block = get_block_to_color(idx, block_size);

	SDL_SetRenderDrawColor(sdl_data->renderer, player->r, player->g,
		player->b, 255);

	SDL_RenderFillRect(sdl_data->renderer, &block);
}

static void draw_elem(t_window *sdl_data, t_vector *block_size, t_vector *idx,
	char representation
)
{
	SDL_Rect block = get_block_to_color(idx, block_size);
	int idx_pattern = -1;

	switch (representation) {
	case -3:
		idx_pattern = 0;
		break;
	case -4:
		idx_pattern = 1;
		break;
	case -5:
		idx_pattern = 2;
		break;
	}

	if (idx_pattern != -1)
		SDL_RenderCopy(sdl_data->renderer,
			sdl_data->pattern[idx_pattern], NULL, &block);
}

static void check_representation(t_window *sdl_map, t_vector *block_size,
	char representation, t_vector *idx
)
{
	t_team *header = sdl_map->list_team;
	int check = 0;

	if (representation == ' ')
		return;
	while (sdl_map->list_team) {
		if (sdl_map->list_team->representation == representation) {
			fill_rect_player(sdl_map, block_size,
				sdl_map->list_team, idx);
			check = 1;
			break;
		}
		sdl_map->list_team = sdl_map->list_team->next;
	}
	sdl_map->list_team = header;
	if (!check)
		draw_elem(sdl_map, block_size, idx, representation);
}

void draw_player(t_window *sdl_map, t_vector *block_size, char **map)
{
	t_vector idx = {0, 0};

	for (; map && map[idx.y]; ++idx.y) {
		idx.x = 0;
		for (; map[idx.y][idx.x] != '\0'; ++idx.x) {
			check_representation(sdl_map, block_size,
				map[idx.y][idx.x], &idx);
		}
	}
}