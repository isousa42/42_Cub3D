#include "cub3d.h"

// FUCTION RC_LOOP - It's the main loop where the raycasting and DDA algorithm happens. It will calculate where to put pixels and ask the draw_line() to draw it in the window
void	rc_loop(t_info *info)
{
	// FLOOR DRAWING
	floor_draw(info);

	// // WALL DRAWING
	info->rc.x = 0;
	while (info->rc.x < info->width) // 640 is width of window
	{
		wall_init(info);
		ray_walking(info);
		// PERFORM DDA ALGORITHM
		dda_algorithm(info);
		wall_calc(info);
		// TEXTURING CALCULATIONS
		wall_text(info);
		while (info->rc.y < info->rc.drawEnd)
		{
			//Cast the texture coordinate to integer and mask with (textHeight - 1) in case of overflow
			info->rc.textY = (int)info->rc.textPos & (textHeight - 1);
			info->rc.textPos += info->rc.step;
			//info->rc.color = info->texture[info->rc.textNum][textHeight * info->rc.textY + info->rc.textX];

			//make color darker for y-sides: R,G,B byte each divided through two with a shift and an and
			if (info->rc.side == 0)
				info->rc.color = info->texture[0][textHeight * info->rc.textY + info->rc.textX];
			else if (info->rc.side == 1)
				info->rc.color = info->texture[1][textHeight * info->rc.textY + info->rc.textX];
			else if (info->rc.side == 2)
				info->rc.color = info->texture[2][textHeight * info->rc.textY + info->rc.textX];
			else if (info->rc.side == 3)
				info->rc.color = info->texture[3][textHeight * info->rc.textY + info->rc.textX];
			info->buff[info->rc.y][info->rc.x] = info->rc.color;
			info->rc.y++;
		}
		info->rc.x++;
		//NEW FOR SPRITES:
		info->sprites.sprites_buff[info->rc.x] = info->rc.perpWallDist;
		
	}
	int x;
	int y;
	x = 0;
	while (x < info->size_list)
	{
		y = 0;
		while (y < ft_strlen(info->map[x]))
		{
			if (info->map[x][y] == '2')
			{
				sprites_draw(info, x, y, 4);
			}
			y++;
		}
		x++;
	}
	//sprites_draw(info, 3, 3, 4);
	
}



int	first_loop(t_info *info)
{
	rc_loop(info);
	if (info->take_pic == 1)
	{
		take_screenshot(info);
	}
	draw_img(info);
	key_hook(info);

	return (0);
}

void	read_file(t_info *info)
{
	
	int fd;
	int ret;
    char *line;
	info->save = NULL;
	int y;
	t_list *lista = NULL;

	ret = 0;
	line = NULL;
	
	fd = open(info->file_path, O_RDONLY);
	if (fd == -1)
	{
		printf("ERROR = NOT ABLE TO READ THE FILE");
		exit(0);
	}
	while ((ret = get_next_line(fd, &line)) > 0)
    {
        if (line[0] == 'R')
			parse_r(info, line);
		else if (line[0] == 'F')
            parse_f(info, line);
		else if (line[0] == 'C')
            parse_c(info, line);
		else if (line[0] == 'N' && line[1] == 'O')
            parse_variable(info, line, 1);
        else if (line[0] == 'S' && line[1] == 'O')
            parse_variable(info, line, 2);
        else if (line[0] == 'W' && line[1] == 'E')
            parse_variable(info, line, 3);
        else if (line[0] == 'E' && line[1] == 'A')
            parse_variable(info, line, 4);
        else if (line[0] == 'S' && line[1] == ' ')
            parse_variable(info, line, 5);
		else
            ft_lstadd_back(&lista, ft_lstnew((void *)line));
	}
	close(fd);
	if (info->width == 1920)
		info->width = 1921;
	if (info->width >= 2560)
		info->width = 2559;
	if (info->height >= 1440)
		info->height = 1439;
	if (info->width <= 9)
		info->width = 10;
	if (info->height <= 9)
		info->height = 10;
	int x;

    x = 0;
	
    info->size_list = ft_lstsize(lista);
    info->map = ft_calloc(info->size_list, sizeof(char *));
    while (lista)
    {
        info->map[x] = ft_strdup(lista->content);
        lista = lista->next;
        x++;
    }
	//info->map[x] = NULL;
	check_errors_map(info->map, info->size_list);

	x = 0;
	while (x < info->size_list)
	{
		y = 0;
		while (y < ft_strlen(info->map[x]))
		{
			if (ft_isalpha(info->map[x][y]) == 1)
			{
				info->posX = x + 0.5;
				info->posY = y + 0.5;
				info->direction = info->map[x][y];
				info->map[x][y] = '0';
				
			}
			y++;
		}
		x++;
	}
}

int		check_arg(char *arg)
{
	if (arg[0] != '-')
		return (-1);
	if (arg[1] != '-')
		return (-1);
	if (arg[2] != 's')
		return (-1);
	if (arg[3] != 'a')
		return (-1);
	if (arg[4] != 'v')
		return (-1);
	if (arg[5] != 'e')
		return (-1);
	return (0);
}

int main(int argc, char **argv)
{
	
	t_info info;
	info.mlx = mlx_init();
	printf("CHEGOU");
	if (argc == 1)
	{
		printf("ERROR = YOU FORGOT TO PUT THE FILE (.cub)");
		exit(0);
	}
	else if (argc == 2 || argc == 3)
		info.file_path = ft_strdup(argv[1]);
	if (argc == 3)
	{
		if ((check_arg(argv[2])) == 0)
			info.take_pic = 1;
		else
		{
			printf("ERROR = IF YOU WANT A SCREENSHOT SPELL IT RIGTH!");
			exit(0);
		}
	}
		
	info.moveSpeed = 0.03;
	info.rotSpeed = 0.03;
	
	read_file(&info);
    ft_init_info(&info);
	init_play_pos(&info);
	init_key(&info);
	info.rgb_floor = create_rgb(info.flagF[0], info.flagF[1], info.flagF[2]);
	info.rgb_ceiling = create_rgb(info.flagC[0], info.flagC[1], info.flagC[2]);
	ft_handle_text(&info);
	info.win = mlx_new_window(info.mlx, info.width, info.height, "cub3D");
	info.img.img = mlx_new_image(info.mlx, info.width, info.height);
	info.img.data = (int *)mlx_get_data_addr(info.img.img, &info.img.bpp, &info.img.size, &info.img.endian);
	mlx_loop_hook(info.mlx, &first_loop, &info);
	mlx_hook(info.win, X_EVENT_KEY_PRESS, 0, &key_press, &info);
	mlx_hook(info.win, 3, 0, &key_release, &info);
    mlx_loop(info.mlx);		
}