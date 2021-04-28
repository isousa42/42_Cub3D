CC	= gcc

RM	= rm -f

NAME	= cub3D

HEADER = cub3d.h
INCLUDE = ../include
MLX = /usr/local/lib
LFLAGS = -lmlx -framework OPENGL -framework AppKit -g
SRCS	= cub3d.c init_text.c init_info.c keys.c floor.c wall.c

OBJS	= $(SRCS:.c=.o)

all:	$(NAME)

$(NAME):	$(OBJS) $(HEADER)
			$(CC) -I $(INCLUDE) -o $(NAME) $(OBJS) -L $(MLX) $(LFLAGS)

clean:
			$(RM) $(OBJS)

fclean:	clean
			$(RM) $(NAME)

re:	fclean all

.PHONY: all clean fclean re
