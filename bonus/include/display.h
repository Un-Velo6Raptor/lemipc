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
# include <SDL2/SDL_image.h>
# include "transmission.h"
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

	SDL_Texture *image[7];
	SDL_Texture *pattern[7];
	int tools_used;

	t_team *list_team;
} t_window;

void destroy_sdl_tools(t_window *sdl_data);
int create_window(t_window *sdl_data, char *window_name);

int draw_map_sdl(t_window *sdl_map, char **map);
void draw_player(t_window *sdl_map, t_vector *block_size, char **map);
int draw_tools(t_window *sdl_data);

int check_mouse_click(t_data *data, t_window *sdl_data, SDL_Event *ev);
t_vector get_block_tools(t_window *sdl_data);

int tools_manage_wall(t_data *data, t_window *sdl_data, SDL_Event *ev);
int tools_manage_leaf(t_data *data, t_window *sdl_data, SDL_Event *ev);
int tools_manage_water(t_data *data, t_window *sdl_data, SDL_Event *ev);
int tools_manage_rubber(t_data *data, t_window *sdl_data, SDL_Event *ev);
int tools_manage_reset(t_data *data, t_window *sdl_data, SDL_Event *ev);
int tools_manage_player(t_data *data, t_window *sdl_data, SDL_Event *ev);

#endif //PSU_LEMIPC_2017_DISPLAY_H
