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

	printf("Print player Rect\n");
	SDL_SetRenderDrawColor(sdl_data->renderer, player->r, player->g, player->b, 255);

	block.x = MSG_WIDTH + (idx->x * block_size->x) + 1;
	block.w = block_size->x - 1;

	block.y = (idx->y * block_size->y) + 1;
	block.h = block_size->y - 1;

	printf("RECT: (%d, %d), (%d, %d)\n", block.x, block.w, block.y, block.h);

	SDL_RenderFillRect(sdl_data->renderer, &block);
}

static void check_representation(t_window *sdl_map, t_vector *block_size,
	char representation, t_vector *idx
)
{
	t_team *tmp = sdl_map->list_team;

	if (representation == ' ')
		return;
	while (tmp) {
		if (tmp->representation == representation)
			fill_rect_player(sdl_map, block_size, tmp, idx);
		tmp = tmp->next;
	}
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