#include "cub3d.h"

void    ft_init_info(t_info *info)
{
	info->sprites.sprites_buff = ft_calloc(info->width, sizeof(double *));
}

void	init_play_pos(t_info *info)
{
	if (info->direction == 'N')
	{
		//Initial Direction the player is looking
		info->dirX = -1;
		info->dirY = 0.0;

		//Initial FOV
		info->planeX = 0.0;
		info->planeY = 0.66;
	}
	else if (info->direction == 'S')
	{
		//Initial Direction the player is looking
		info->dirX = 1;
		info->dirY = 0.0;

		//Initial FOV
		info->planeX = 0.0;
		info->planeY = -0.66;
	}
	else if (info->direction == 'W')
	{
		//Initial Direction the player is looking
		info->dirX = 0.0;
		info->dirY = -1;

		//Initial FOV
		info->planeX = -0.66;
		info->planeY = 0.0;
	}
	else if (info->direction == 'E')
	{
		//Initial Direction the player is looking
		info->dirX = 0.0;
		info->dirY = 1;

		//Initial FOV
		info->planeX = 0.66;
		info->planeY = 0.0;
	}
}