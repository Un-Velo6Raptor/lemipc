/*
** EPITECH PROJECT, 2018
** PSU_lemipc_2017
** File description:
** Created by martin.januario@epitech.eu,
*/

#include "config.h"
#include "display.h"

static void fill_rect_player(t_window *sdl_data, t_vector *block_size,
	t_team *player, t_vector *idx
)
{
	SDL_Rect block;

	SDL_SetRenderDrawColor(sdl_data->renderer, player->r, player->g,
		player->b, 255);

	block.x = MSG_WIDTH + (idx->x * block_size->x) + 1;
	block.w = block_size->x - 1;

	block.y = (idx->y * block_size->y) + 1;
	block.h = block_size->y - 1;

	SDL_RenderFillRect(sdl_data->renderer, &block);
}

static void check_representation(t_window *sdl_map, t_vector *block_size,
	char representation, t_vector *idx
)
{
	t_team *header = sdl_map->list_team;

	if (representation == ' ')
		return;
	while (sdl_map->list_team) {
		if (sdl_map->list_team->representation == representation) {
			fill_rect_player(sdl_map, block_size,
				sdl_map->list_team, idx);
			break;
		}
		sdl_map->list_team = sdl_map->list_team->next;
	}
	sdl_map->list_team = header;
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