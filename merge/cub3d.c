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
			info->rc.color = info->texture[info->rc.textNum][textHeight * info->rc.textY + info->rc.textX];

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
	sprites_draw(info, 3, 3, 4);
}

int	first_loop(t_info *info)
{
	rc_loop(info);
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
	
	fd = open("cub3D.cub", O_RDONLY);
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

	int x;
    int size;

    x = 0;
    info->size_list = ft_lstsize(lista);
    info->save = ft_calloc(size, sizeof(char **));
    while (lista != NULL)
    {
        info->save[x] = ft_strdup(lista->content);
        lista = lista->next;
        x++;
    }
	info->save[x] = NULL;
	x = 0;
	while (info->save[x])
	{
		y = 0;
		while (y < ft_strlen(info->save[x]))
		{
			if (ft_isalpha(info->save[x][y]) == 1)
			{
				info->posX = x + 0.5;
				info->posY = y + 0.5;
				info->save[x][y] = '0';
			}
			y++;
		}
		x++;
	}
	
	// x = 0;
	// y = 0;
	// while (info->save[x])
	// {
	// 	printf("%s\n", info->save[x]);
	// 	x++;
	// }


    //check_errors_map(save, size);

	
}

int main()
{
	
	t_info info;
	info.mlx = mlx_init();
	
	//info.map = NULL;
	read_file(&info);
	//initialize the variables
    ft_init_info(&info);
	init_play_pos(&info);
	init_key(&info);
	init_map(&info);

	info.rgb_floor = create_rgb(info.flagF[0], info.flagF[1], info.flagF[2]);
	info.rgb_ceiling = create_rgb(info.flagC[0], info.flagC[1], info.flagC[2]);
	//printf("%d", info.rgb_ceiling);

	ft_handle_text(&info);
    
	// Create the window
	info.win = mlx_new_window(info.mlx, info.width, info.height, "cub3D");
	
    
	// Creating the image
	info.img.img = mlx_new_image(info.mlx, info.width, info.height);
	info.img.data = (int *)mlx_get_data_addr(info.img.img, &info.img.bpp, &info.img.size, &info.img.endian);
    
	// LOOPS OF MLX
	mlx_loop_hook(info.mlx, &first_loop, &info);
	mlx_hook(info.win, X_EVENT_KEY_PRESS, 0, &key_press, &info);
	mlx_hook(info.win, 3, 0, &key_release, &info);
    mlx_loop(info.mlx);		
}