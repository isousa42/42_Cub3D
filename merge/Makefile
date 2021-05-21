CC	= gcc

RM	= rm -f

NAME	= cub3D

HEADER = cub3d.h
INCLUDE = ../include
MLX = /usr/local/lib
LFLAGS = -lmlx -framework OPENGL -framework AppKit -g
SRCS	= cub3d.c init_text.c init_info.c keys.c floor.c wall.c utils.c \
			 sprites.c gnl_utils.c get_next_line.c check_errors_var.c \
			 parse_utils.c lst_utils.c check_errors_map.c screenshot.c \
			 check_args.c read_file.c

OBJS	= $(SRCS:.c=.o)

all:	$(NAME)

$(NAME):	$(OBJS) $(HEADER)
			$(CC) -I $(INCLUDE) -o $(NAME) $(OBJS) -L $(MLX) $(LFLAGS)

clean:
			$(RM) $(OBJS)

fclean:	clean
			$(RM) $(NAME)
			$(RM) *.bmp

re:	fclean all

.PHONY: all clean fclean re
