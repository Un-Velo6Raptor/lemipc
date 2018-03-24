/*
** EPITECH PROJECT, 2018
** PSU_lemipc_2017
** File description:
** Created by martin.januario@epitech.eu,
*/

#include "transmission.h"
#include "display.h"
#include "config.h"

static int manage_features(t_data *data, t_window *sdl_data, SDL_Event *ev)
{
	int (*tools_manage[])(t_data *, t_window *, SDL_Event *) = {
		tools_manage_wall, tools_manage_leaf, tools_manage_water,
		tools_manage_rubber, tools_manage_reset, tools_manage_player};

	if (sdl_data->tools_used == -1 || sdl_data->tools_used >= 7)
		return (0);
	return (tools_manage[sdl_data->tools_used](data, sdl_data, ev));
}

static int manage_tools_select(t_window *sdl_data, SDL_Event *ev)
{
	t_vector size = get_block_tools(sdl_data);
	int result = (ev->button.x - MSG_WIDTH) / size.x;

	if (result == sdl_data->tools_used) {
		sdl_data->tools_used = -1;
		return (0);
	}
	sdl_data->tools_used = result;
	return (0);
}

int check_mouse_click(t_data *data, t_window *sdl_data, SDL_Event *ev)
{
	if (sdl_data->tools_used != -1 &&
		ev->button.y < WINDOW_HEIGHT - TOOLS_HEIGHT) {
		manage_features(data, sdl_data, ev);
	} else if (ev->button.x > MSG_WIDTH &&
		ev->button.y > WINDOW_HEIGHT - TOOLS_HEIGHT) {
		manage_tools_select(sdl_data, ev);
	}
	return (0);
}
