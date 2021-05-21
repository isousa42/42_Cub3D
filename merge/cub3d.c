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
		take_screenshot(info);
	draw_img(info);
	key_hook(info);

	return (0);
}

int	close_window(t_info *info)
{
	exit(0);
}

int main(int argc, char **argv)
{
	t_info info;
	info.mlx = mlx_init();
	check_args(argc, argv, &info);
	read_file(&info);
    ft_init_info(&info);
	init_play_pos(&info);
	init_key(&info);
	ft_handle_text(&info);
	info.win = mlx_new_window(info.mlx, info.width, info.height, "cub3D");
	info.img.img = mlx_new_image(info.mlx, info.width, info.height);
	info.img.data = (int *)mlx_get_data_addr(info.img.img, &info.img.bpp, &info.img.size, &info.img.endian);
	mlx_loop_hook(info.mlx, &first_loop, &info);
	mlx_hook(info.win, X_EVENT_KEY_PRESS, 0, &key_press, &info);
	mlx_hook(info.win, 3, 0, &key_release, &info);
	mlx_hook(info.win, 17, 1L<<17, &close_window, &info);
    mlx_loop(info.mlx);		
}