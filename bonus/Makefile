##
## EPITECH PROJECT, 2018
## lemipc
## File description:
## Created by martin.januario@epitech.eu
##

SRC		=	../src/init/initialize_memory_shared.c		\
			../src/init/initialize_semaphore.c		\
			../src/init/initialize_msg_queue.c		\
			../src/manage/manage_memory_shared.c		\
			../src/manage/manage_msg_queue.c		\
			../src/manage/manage_semaphore.c		\
			../src/parsing/check_arg.c			\
			../src/config.c					\
			../src/ia/end.c					\
			../src/ia/game.c				\
			../src/ia/ia.c					\
			../src/ia/placement.c				\
			../src/ia/target.c				\
			../src/basics.c

SRC_DISPLAY	=	src/display/game.c				\
			src/main.c					\
			src/display/clear_ressources.c			\
			src/display/init_window.c			\
			src/display/draw_map.c				\
			src/display/draw_player.c			\
			src/display/draw_tools.c			\
			src/parsing/manage_click.c			\
			src/parsing/check_arg.c

SRC_MANAGE	=	src/manage_map/manage_leaf.c			\
			src/manage_map/manage_wall.c			\
			src/manage_map/manage_water.c			\
			src/manage_map/manage_rubber.c			\
			src/manage_map/manage_reset.c			\
			src/manage_map/manage_player.c

OBJ		=	$(SRC:.c=.o)					\
			$(SRC_MANAGE:.c=.o)				\
			$(SRC_DISPLAY:.c=.o)

SDL_CFLAGS	:=	$(shell sdl2-config --cflags)

SDL_LDFLAGS	:=	$(shell sdl2-config --libs)

CFLAGS		=	-W -Wall -Wextra $(SDL_CFLAGS)			\
			-I include/					\
			-I ../include/ -I ../include/ia/

LDFLAGS		=	-lpthread -lrt -lSDL2_image -lSDL2_ttf $(SDL_LDFLAGS)

NAME		=	ipc_map

all:			$(NAME)

$(NAME):		$(OBJ)
			gcc -o $(NAME) $(OBJ) $(LDFLAGS)

clean:
			rm -f $(OBJ)

fclean:			clean
			rm -f $(NAME)

re:			fclean all

debug:			CFLAGS += -ggdb3

debug:			re

install:
			sudo apt-get install libsdl2-dev
			sudo apt-get install libsdl2-image-dev
			sudo apt-get install libsdl2-tff-dev

.PHONY:			all clean fclean re debug install
