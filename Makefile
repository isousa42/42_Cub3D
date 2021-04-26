CC	= gcc

RM	= rm -f

NAME	= cub3D

INCLUDE = ../include
MLX = /usr/local/lib
LFLAGS = -lmlx -framework OPENGL -framework AppKit
SRCS	= cub3d.c

OBJS	= $(SRCS:.c=.o)

all:	$(NAME)

$(NAME):	$(OBJS)
			$(CC) -I $(INCLUDE) -o $(NAME) $(OBJS) -L $(MLX) $(LFLAGS)

clean:
			$(RM) $(OBJS)

fclean:	clean
			$(RM) $(NAME)

re:	fclean all

.PHONY: all clean fclean re
