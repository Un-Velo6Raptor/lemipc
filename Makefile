##
## EPITECH PROJECT, 2018
## lemipc
## File description:
## Created by martin.januario@epitech.eu
##

SRC	=	src/check_arg.c				\
		src/initialize_memory_shared.c		\
		src/main.c

OBJ	=	$(SRC:.c=.o)

CFLAGS	=	-W -Wall -Werror -Wextra -I include/

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
