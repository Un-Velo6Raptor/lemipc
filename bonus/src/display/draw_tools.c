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

static void tool_used(t_window *sdl_data, SDL_Rect *texture_dest)
{
	SDL_SetRenderDrawColor(sdl_data->renderer, 255, 255, 255, 100);
	SDL_SetRenderDrawBlendMode(sdl_data->renderer, SDL_BLENDMODE_BLEND);
	SDL_RenderFillRect(sdl_data->renderer, texture_dest);
}

static int print_team_wheel(t_window *sdl_data, SDL_Rect *texture_dest)
{
	SDL_Color white = {255, 255, 255, 255};
	char tmp[3];
	SDL_Surface *surfaceMessage = TTF_RenderText_Solid(sdl_data->fonts_team,
		tmp, white);
	SDL_Texture *message = SDL_CreateTextureFromSurface(sdl_data->renderer,
		surfaceMessage);

	sprintf(tmp, "%d", sdl_data->team_wheel);
	texture_dest->x = WINDOW_WIDTH - 50;
	texture_dest->y += 40;
	texture_dest->w = 30;
	texture_dest->h = 30;
	surfaceMessage = TTF_RenderText_Solid(sdl_data->fonts_team,
		tmp, white);
	message = SDL_CreateTextureFromSurface(sdl_data->renderer,
		surfaceMessage);
	SDL_RenderCopy(sdl_data->renderer, message, NULL, texture_dest);
	return (0);
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
		if (sdl_data->tools_used == idx)
			tool_used(sdl_data, &texture_dest);
		texture_dest.x += block.x + 1;
	}
	return (print_team_wheel(sdl_data, &texture_dest));
}