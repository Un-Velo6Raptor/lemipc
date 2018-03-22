/*
** EPITECH PROJECT, 2018
** PSU_lemipc_2017
** File description:
** Created by martin.januario@epitech.eu,
*/

#include "display.h"

const int WINDOW_WIDTH = 1600;
const int WINDOW_HEIGHT = 900;

const int MSG_WIDTH = 500;
const int TOOLS_HEIGHT = 100;

void create_window(t_window *sdl_data, char *window_name)
{
	SDL_Init(SDL_INIT_VIDEO);

	sdl_data->window = SDL_CreateWindow(window_name, SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT,
		SDL_WINDOW_OPENGL);
	sdl_data->renderer = SDL_CreateRenderer(sdl_data->window, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	sdl_data->list_team = NULL;
}