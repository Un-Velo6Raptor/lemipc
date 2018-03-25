/*
** EPITECH PROJECT, 2018
** PSU_lemipc_2017
** File description:
** Created by martin.januario@epitech.eu,
*/

#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/sem.h>
#include "transmission.h"
#include "display.h"
#include "config.h"

static int draw_interface(t_data *data, t_window *sdl_data, int last_tools, int *check)
{
	struct sembuf sops;
	SDL_Rect loading_position = {MSG_WIDTH, 0, WINDOW_WIDTH - MSG_WIDTH,
		WINDOW_HEIGHT - TOOLS_HEIGHT};

	sops.sem_num = 0;
	sops.sem_flg = 0;
	if (sdl_data->tools_used != -1 && last_tools == -1) {
		*check = 30;
		SDL_SetRenderDrawColor(sdl_data->renderer, 255, 255, 255, 255);
		draw_map_sdl(sdl_data, data->map);
		draw_tools(sdl_data);
		SDL_RenderCopy(sdl_data->renderer, sdl_data->loading, NULL,
			&loading_position);
		SDL_RenderPresent(sdl_data->renderer);
		sops.sem_op = -1;
		semop(data->sem_id, &sops, 1);
		usleep(300000);
	} else if (sdl_data->tools_used == -1 && last_tools != -1) {
		sops.sem_op = 1;
		semop(data->sem_id, &sops, 1);
	}
	SDL_SetRenderDrawColor(sdl_data->renderer, 255, 255, 255, 255);
	draw_map_sdl(sdl_data, data->map);
	draw_tools(sdl_data);
	return (0);
}

static void update_team_adder(t_window *sdl_data, int scroll)
{
	if (scroll > 0 && sdl_data->team_wheel < strlen(TEAMS) - 1)
		sdl_data->team_wheel++;
	else if (scroll < 0 && sdl_data->team_wheel > 0)
		sdl_data->team_wheel--;
}

static int manage_event(t_data *data, t_window *sdl_data, SDL_Event *event)
{
	static bool check = false;

	if (event->type == SDL_MOUSEBUTTONDOWN)
		check = true;
	else if (event->type == SDL_MOUSEBUTTONUP ||
		(event->button.y > WINDOW_HEIGHT - TOOLS_HEIGHT &&
			event->button.x > MSG_WIDTH))
		check = false;
	if (event->type == SDL_MOUSEWHEEL)
		update_team_adder(sdl_data, event->wheel.y);
	return ((check) ? check_mouse_click(data, sdl_data, event) : 0);
}

static int loop_game(t_data *data, t_window *sdl_data)
{
	static int last_tools = -1;
	bool running = true;
	SDL_Event event;
	int check = 0;

	while (running) {
		SDL_SetRenderDrawColor(sdl_data->renderer, 255, 255, 255, 255);
		SDL_RenderClear(sdl_data->renderer);
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT ||
				(event.type == SDL_KEYDOWN &&
					event.key.keysym.sym == SDLK_ESCAPE))
				running = false;
			else if (!check)
				manage_event(data, sdl_data, &event);
		}
		if (draw_interface(data, sdl_data, last_tools, &check) == 84)
			running = false;
		last_tools = sdl_data->tools_used;
		SDL_RenderPresent(sdl_data->renderer);
		if (check)
			check--;
	}
	destroy_sdl_tools(sdl_data);
	return (0);
}

int graphical_display(t_data *data)
{
	t_window sdl_data;
	struct sembuf sops;
	int ret = 0;

	data->map = get_the_map(data);
	if (!data->map)
		return (84);
	srandom(time(NULL));
	if (create_window(&sdl_data, "Lemipc graphical bonus"))
		return (84);
	ret = loop_game(data, &sdl_data);
	if (sdl_data.tools_used != -1) {
		sops.sem_num = 0;
		sops.sem_flg = 0;
		sops.sem_op = 1;
		semop(data->sem_id, &sops, 1);
	}
	return (ret);
}