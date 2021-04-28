#include "cub3d.h"


void	draw_img(t_info *info)
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			info->img.data[y * width + x] = info->buff[y][x];
		}
	}
	mlx_put_image_to_window(info->mlx, info->win, info->img.img, 0, 0);
}

// FUCTION RC_LOOP - It's the main loop where the raycasting and DDA algorithm happens. It will calculate where to put pixels and ask the draw_line() to draw it in the window

void	rc_loop(t_info *info)
{
	// FLOOR DRAWING
	floor_draw(info);

	// // WALL DRAWING
	info->rc.x = 0;
	while (info->rc.x < width) // 640 is width of window
	{
		wall_init(info);
		ray_walking(info);
	// PERFORM DDA ALGORITHM
		dda_algorithm(info);
		

		//Calculate distance of perpendicular ray (Euclidean distance will give the fisheye effect
		if (info->rc.side == 0)
			info->rc.perpWallDist = (info->rc.mapX - info->posX + (1 - info->rc.stepX) / 2) / info->rc.rayDirX;
		else
			info->rc.perpWallDist = (info->rc.mapY - info->posY + (1 - info->rc.stepY) / 2) / info->rc.rayDirY;
	
		//Calculate height of line to draw
		info->rc.lineHeight = (int)(height / info->rc.perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		info->rc.drawStart = -info->rc.lineHeight / 2 + height / 2;
		if (info->rc.drawStart < 0)
			info->rc.drawStart = 0;
		info->rc.drawEnd = info->rc.lineHeight / 2 + height / 2;
		if (info->rc.drawEnd >= height)
			info->rc.drawEnd = height - 1;
		
		// TEXTURING CALCULATIONS
		
		info->rc.textNum = info->map[info->rc.mapX][info->rc.mapY] - 1; // this variable is the value of the current map square minus 1, because there is the texture zero, but in the map the 0 has no texture. To be able to use the texture number zero, we need to subtract 1.

		//The value wallX represents the exact value where the wall was hit. This is needed to know which x-coordinate of the texture we have to use. 
		//This is calculated by first calculating the exact x and y coordinate in the world and then subtrating the integer value of the wall. 
		//Even if it is called wallX, it's actually an y-coordinate of the wall if side == 1, but it's always the x-coordinate of the texture.
		if (info->rc.side == 0)
			info->rc.wallX = info->posY + info->rc.perpWallDist * info->rc.rayDirY;
		else
			info->rc.wallX = info->posX + info->rc.perpWallDist * info->rc.rayDirX;
		info->rc.wallX -= floor(info->rc.wallX);

		//X-coordinate of the texture, based on wallX
		info->rc.textX = (int)(info->rc.wallX * (double)textWidth);
		if (info->rc.side == 0 && info->rc.rayDirX > 0)
			info->rc.textX = textWidth - info->rc.textX - 1;
		if (info->rc.side == 1 && info->rc.rayDirY < 0)
			info->rc.textX = textWidth - info->rc.textX - 1;
		
		//How much to increase the texture coordinate perscreen pixel
		info->rc.step = 1.0 * textHeight / info->rc.lineHeight;
		// Starting texture coordinate
		info->rc.textPos = (info->rc.drawStart - height / 2 + info->rc.lineHeight / 2) * info->rc.step;
		info->rc.y = info->rc.drawStart;
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
	init_map(&info);

	//initialize the variables of the info struct
	ft_init_info(&info);
	
	//Create buff and textures
	if (ft_handle_text(&info) != 0)
		return (-1);

	info.win = mlx_new_window(info.mlx, width, height, "mlx");

	// Creating the image
	info.img.img = mlx_new_image(info.mlx, width, height);
	info.img.data = (int *)mlx_get_data_addr(info.img.img, &info.img.bpp, &info.img.size, &info.img.endian);


	mlx_loop_hook(info.mlx, &first_loop, &info);
	mlx_hook(info.win, X_EVENT_KEY_PRESS, 0, &key_press, &info);
	mlx_hook(info.win, 3, 0, &key_release, &info);

    mlx_loop(info.mlx);		
}
