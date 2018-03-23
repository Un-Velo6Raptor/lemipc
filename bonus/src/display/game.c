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

static char **wait_free_map(t_data *data, struct sembuf *sops, t_window *sdl_map)
{
	(void)sdl_map;
	sops->sem_op = -1;
	semop(data->sem_id, sops, 1);

	char **tmp = get_the_map(data);
	if (!tmp) {
		sops->sem_op = 1;
		semop(data->sem_id, sops, 1);
		return (NULL);
	}
	sops->sem_op = 1;
	semop(data->sem_id, sops, 1);
	return (tmp);
}

static int draw_interface(t_data *data, struct sembuf *sops, t_window *sdl_data)
{
	char **map = NULL;

	SDL_SetRenderDrawColor(sdl_data->renderer, 255, 255, 255, 255);
	map = wait_free_map(data, sops, sdl_data);
	if (map) {
		draw_map_sdl(sdl_data, map);
	}
	free_tab(map);
	return (0);
}

static int loop_game(t_data *data, struct sembuf *sops, t_window *sdl_data)
{
	bool running = true;
	SDL_Event event;

	while (running) {
		SDL_SetRenderDrawColor(sdl_data->renderer, 255, 255, 255, 255);
		SDL_RenderClear(sdl_data->renderer);
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT ||
				(event.type == SDL_KEYDOWN &&
					event.key.keysym.sym == SDLK_ESCAPE)) {
				running = false;
			}
		}
		if (draw_interface(data, sops, sdl_data) == 84)
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

	srandom(time(NULL));
	sops.sem_num = 0;
	sops.sem_flg = 0;
	create_window(&sdl_data, "Lemipc graphical bonus");
	return (loop_game(data, &sops, &sdl_data));
}