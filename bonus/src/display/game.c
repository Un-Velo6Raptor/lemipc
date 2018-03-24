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

static int draw_interface(t_data *data, t_window *sdl_data)
{
	char **map = NULL;
	static int last_tools = -1;
	struct sembuf sops;

	sops.sem_num = 0;
	sops.sem_flg = 0;
	if (sdl_data->tools_used != -1 && last_tools == -1) {
		sops.sem_op = -1;
		semop(data->sem_id, &sops, 1);
		usleep(300000);
	} else if (sdl_data->tools_used == -1 && last_tools != -1) {
		sops.sem_op = 1;
		semop(data->sem_id, &sops, 1);
	}
	SDL_SetRenderDrawColor(sdl_data->renderer, 255, 255, 255, 255);
	map = get_the_map(data);
	if (map) {
		draw_map_sdl(sdl_data, map);
	}
	draw_tools(sdl_data);
	free_tab(map);
	last_tools = sdl_data->tools_used;
	return (0);
}

static int loop_game(t_data *data, t_window *sdl_data)
{
	bool running = true;
	SDL_Event event;
	bool check = false;

	while (running) {
		SDL_SetRenderDrawColor(sdl_data->renderer, 255, 255, 255, 255);
		SDL_RenderClear(sdl_data->renderer);
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT ||
				(event.type == SDL_KEYDOWN &&
					event.key.keysym.sym == SDLK_ESCAPE)) {
				running = false;
			} else if (event.type == SDL_MOUSEBUTTONDOWN)
				check = true;
			else if (event.type == SDL_MOUSEBUTTONUP)
				check = false;
			if (check)
				check_mouse_click(data, sdl_data, &event);
		}
		if (draw_interface(data, sdl_data) == 84)
			running = false;
		SDL_RenderPresent(sdl_data->renderer);
	}
	destroy_sdl_tools(sdl_data);
	return (0);
}

int game(t_data *data)
{
	t_window sdl_data;
	struct sembuf sops;
	int ret = 0;

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