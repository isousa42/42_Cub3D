#include "cub3d.h"

void	text_calc(t_info *info)
{
	int	norminette;

	while (info->rc.y < info->rc.drawEnd)
	{
		info->rc.textY = (int)info->rc.textPos & (TEXTHEIGHT - 1);
		info->rc.textPos += info->rc.step;
		norminette = TEXTHEIGHT * info->rc.textY + info->rc.textX;
		if (info->rc.side == 0)
			info->rc.color = info->texture[0][norminette];
		else if (info->rc.side == 1)
			info->rc.color = info->texture[1][norminette];
		else if (info->rc.side == 2)
			info->rc.color = info->texture[2][norminette];
		else if (info->rc.side == 3)
			info->rc.color = info->texture[3][norminette];
		info->buff[info->rc.y][info->rc.x] = info->rc.color;
		info->rc.y++;
	}
}

void	sprites_calc(t_info *info)
{
	int	x;
	int	y;

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
}

void	rc_loop(t_info *info)
{
	floor_draw(info);
	info->rc.x = 0;
	while (info->rc.x < info->width)
	{
		wall_init(info);
		ray_walking(info);
		dda_algorithm(info);
		wall_calc(info);
		wall_text(info);
		text_calc(info);
		info->rc.x++;
		info->sprites.sprites_buff[info->rc.x] = info->rc.perpWallDist;
	}
	sprites_calc(info);
}

int	first_loop(t_info *info)
{
	if (info->take_pic == 1)
	{
		take_screenshot(info);
		free(info->texture);
		free(info->buff);
		free(info->map);
		close_window(info);
	}
	rc_loop(info);
	draw_img(info);
	key_hook(info);
	return (0);
}

int	main(int argc, char **argv)
{
	t_info	info;

	info.mlx = mlx_init();
	check_args(argc, argv, &info);
	init_rgb(&info);
	read_file(&info);
	ft_init_info(&info);
	init_play_pos(&info);
	init_key(&info);
	handle_buff(&info);
	info.win = mlx_new_window(info.mlx, info.width, info.height, "cub3D");
	info.img.img = mlx_new_image(info.mlx, info.width, info.height);
	info.img.data = (int *)mlx_get_data_addr(info.img.img, &info.img.bpp,
			&info.img.size, &info.img.endian);
	mlx_loop_hook(info.mlx, &first_loop, &info);
	mlx_hook(info.win, X_EVENT_KEY_PRESS, 0, &key_press, &info);
	mlx_hook(info.win, 3, 0, &key_release, &info);
	mlx_hook(info.win, 17, 1L << 17, &close_window, &info);
	mlx_loop(info.mlx);
}
