/*
** EPITECH PROJECT, 2018
** PSU_lemipc_2017
** File description:
** Created by martin.januario@epitech.eu,
*/

#include "display.h"

void destroy_sdl_tools(t_window *sdl_data)
{
	SDL_DestroyRenderer(sdl_data->renderer);
	SDL_DestroyWindow(sdl_data->window);
	SDL_Quit();
}