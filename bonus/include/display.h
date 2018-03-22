/*
** EPITECH PROJECT, 2018
** PSU_lemipc_2017
** File description:
** Created by martin.januario@epitech.eu,
*/

#ifndef PSU_LEMIPC_2017_DISPLAY_H
# define PSU_LEMIPC_2017_DISPLAY_H

# include <stdio.h> // TODO: deleted it
# include <SDL2/SDL.h>
# include "config.h"

extern const int WINDOW_WIDTH;
extern const int WINDOW_HEIGHT;

extern const int MSG_WIDTH;
extern const int TOOLS_HEIGHT;

typedef struct s_team {
	char representation;

	int r;
	int g;
	int b;
	struct s_team *next;
} t_team;

typedef struct s_window {
	SDL_Window *window;
	SDL_Renderer *renderer;

	t_team *list_team;
} t_window;

void destroy_sdl_tools(t_window *sdl_data);
void create_window(t_window *sdl_data, char *window_name);

int draw_map_sdl(t_window *sdl_map, char **map);
void draw_player(t_window *sdl_map, t_vector *block_size, char **map);

#endif //PSU_LEMIPC_2017_DISPLAY_H
