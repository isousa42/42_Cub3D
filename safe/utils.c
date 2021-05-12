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
