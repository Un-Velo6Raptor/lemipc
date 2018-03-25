/*
** EPITECH PROJECT, 2018
** PSU_lemipc_2017
** File description:
** Created by martin.januario@epitech.eu,
*/

#include "display.h"

const int WINDOW_WIDTH = 1000;

const int WINDOW_HEIGHT = 1000;

const int MSG_WIDTH = 0;

const int TOOLS_HEIGHT = 200;

static const char *const PATH_TEXTURE[7] = {"extra/texture_wall.PNG",
	"extra/texture_leaf.PNG", "extra/texture_water.PNG",
	"extra/texture_rubber.PNG", "extra/texture_reset.PNG",
	"extra/texture_player.PNG", 0};

static const char *const PATH_PATTERN[4] = {"extra/pattern_wall.png",
	"extra/pattern_leaf.png", "extra/pattern_water.jpg", 0};

static const char *const PATH_FONTS = "extra/fonts_team.ttf";

static int create_pattern_sdl(t_window *sdl_data)
{
	unsigned int idx = 0;
	SDL_Surface *tmp;
	int ret = 0;

	for (; PATH_PATTERN[idx]; ++idx) {
		tmp = IMG_Load(PATH_PATTERN[idx]);
		sdl_data->pattern[idx] = SDL_CreateTextureFromSurface(
			sdl_data->renderer, tmp);
		if (!sdl_data->pattern[idx])
			return (84);
		SDL_FreeSurface(tmp);
	}
	sdl_data->pattern[idx] = NULL;
	return (ret);
}

static int create_surface_sdl(t_window *sdl_data)
{
	unsigned int idx = 0;
	int ret = 0;

	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
	SDL_Surface *tmp;
	sdl_data->tools_used = -1;
	for (; PATH_TEXTURE[idx]; ++idx) {
		tmp = IMG_Load(PATH_TEXTURE[idx]);
		sdl_data->image[idx] = SDL_CreateTextureFromSurface(
			sdl_data->renderer, tmp);
		if (!sdl_data->image[idx])
			return (84);
		SDL_FreeSurface(tmp);
	}
	sdl_data->image[idx] = NULL;
	if (!ret)
		ret = create_pattern_sdl(sdl_data);
	return (ret);
}

int create_window(t_window *sdl_data, char *window_name)
{
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();

	sdl_data->window = SDL_CreateWindow(window_name,
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH,
		WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
	sdl_data->renderer = SDL_CreateRenderer(sdl_data->window, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	sdl_data->list_team = NULL;
	sdl_data->team_wheel = 0;
	sdl_data->fonts_team = TTF_OpenFont(PATH_FONTS, 10);
	if (!sdl_data->window || !sdl_data->renderer)
		return (84);
	return (create_surface_sdl(sdl_data));
}