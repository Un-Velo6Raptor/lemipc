##
## EPITECH PROJECT, 2018
## lemipc
## File description:
## Created by martin.januario@epitech.eu
##

SRC	=	src/check_arg.c				\
		src/init/initialize_memory_shared.c	\
		src/init/initialize_semaphore.c		\
		src/init/initialize_msg_queue.c		\
		src/manage/manage_memory_shared.c	\
		src/manage/manage_semaphore.c		\
		src/manage/manage_msg_queue.c		\
		src/game.c				\
		src/basics.c				\
		src/main.c

OBJ	=	$(SRC:.c=.o)

CFLAGS	=	-W -Wall -Wextra -I include/

LDFLAGS	=	-lpthread -lrt

NAME	=	lemipc

all:		$(NAME)

$(NAME):	$(OBJ)
		gcc -o $(NAME) $(OBJ) $(LDFLAGS)

clean:
		rm -f $(OBJ)

fclean:		clean
		rm -f $(NAME)

re:		fclean all

debug:		CFLAGS += -ggdb3

debug:		re

.PHONY:		all clean fclean re debug
