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
			if (info->rc.side == 1)
				info->rc.color = (info->rc.color >> 1) & 8355711;
			info->buff[info->rc.y][info->rc.x] = info->rc.color;
			info->rc.y++;
		}
		info->rc.x++;
	}
}

int	first_loop(t_info *info)
{
	rc_loop(info);
	draw_img(info);
	key_hook(info);

	return (0);
}

int main()
{
	t_info info;
	info.mlx = mlx_init();

	//initialize the variables
    ft_init_info(&info);
	init_play_pos(&info);
	init_key(&info);
	init_map(&info);
	int r = 220;
	int g = 100;
	int b = 0;

	info.rgb_floor = create_rgb(r, g, b);
	info.rgb_ceiling = create_rgb(b, g, r);

	//Create buff and textures
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