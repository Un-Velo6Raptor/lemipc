/*
** EPITECH PROJECT, 2018
** PSU_lemipc_2017
** File description:
** Created by martin.januario@epitech.eu,
*/

#include "config.h"
#include "display.h"

t_vector get_block_tools(t_window *sdl_data)
{
	int size = 0;
	t_vector result = {-1, -1};

	for (; sdl_data->image[size]; ++size);
	if (size) {
		result.y = TOOLS_HEIGHT;
		result.x = (WINDOW_WIDTH - MSG_WIDTH) / size;
	}
	return (result);
}

int draw_tools(t_window *sdl_data)
{
	SDL_Rect texture_dest;
	t_vector block = get_block_tools(sdl_data);

	if (block.x == -1)
		return (84);
	texture_dest.x = MSG_WIDTH;
	texture_dest.y = WINDOW_HEIGHT - TOOLS_HEIGHT + 1;
	texture_dest.w = block.x;
	texture_dest.h = block.y;
	for (int idx = 0; sdl_data->image[idx]; ++idx) {
		SDL_SetRenderDrawColor(sdl_data->renderer, 0, 0, 0, 255);
		SDL_RenderCopy(sdl_data->renderer, sdl_data->image[idx], NULL,
			&texture_dest);
		SDL_RenderDrawLine(sdl_data->renderer, texture_dest.x - 1,
			texture_dest.y, texture_dest.x - 1,
			texture_dest.y + texture_dest.h);
		if (sdl_data->tools_used == idx) {
			SDL_SetRenderDrawColor(sdl_data->renderer, 255, 255, 255, 100);
			SDL_SetRenderDrawBlendMode(sdl_data->renderer, SDL_BLENDMODE_BLEND);
			SDL_RenderFillRect(sdl_data->renderer, &texture_dest);
		}
		texture_dest.x += block.x + 1;
	}
	return (0);
}