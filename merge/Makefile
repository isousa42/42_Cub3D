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
			 check_args.c read_file.c check_errors_map_utils.c utils_2.c \
			 keys_utils.c

SRCS_BONUS	= cub3d.c init_text_bonus.c init_info.c keys_bonus.c floor_bonus.c \
				wall.c utils.c \
				sprites.c gnl_utils.c get_next_line.c check_errors_var.c \
				parse_utils.c lst_utils.c check_errors_map.c screenshot.c \
				check_args.c read_file.c check_errors_map_utils.c utils_2.c \
				keys_utils.c

OBJS	= $(SRCS:.c=.o)

OBJS_BONUS	= $(SRCS_BONUS:.c=.o)

all:	$(NAME)

$(NAME):	$(OBJS) $(HEADER)
			$(CC) -I $(INCLUDE) -o $(NAME) $(OBJS) -L $(MLX) $(LFLAGS)

bonus:	$(OBJS_BONUS) $(HEADER)
		$(CC) -I $(INCLUDE) -o $(NAME) $(OBJS_BONUS) -L $(MLX) $(LFLAGS)

clean:
		$(RM) $(OBJS) $(OBJS_BONUS)

fclean:	clean
		$(RM) $(NAME)
		$(RM) *.bmp

re:	fclean all

.PHONY: all bonus clean fclean re
