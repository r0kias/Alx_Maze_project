SRC		=	src/main.c	\
			src/color.c	\
			src/map.c 	\
			src/SDL2_utils.c\
			src/3d_render.c

NAME	=	maze

CC		=	gcc

RM		=	rm -f

OBJ		=	$(SRC:.c=.o)

CFLAGS	=	-Wall -Werror -Wextra -pedantic -std=gnu89 -g
CFLAGS	+=	-I headers

LDLIBS	=	-lSDL2 -lm

all		:	$(NAME)

$(NAME)	:	$(OBJ)
			$(CC) -o $(NAME) $(OBJ) $(LDLIBS)

clean	:
			$(RM) $(OBJ)

fclean	:	clean
			$(RM) $(NAME)

re		:	fclean all

.PHONY	:	all clean fclean re
