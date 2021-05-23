#include "cub3d.h"

void	init_rgb(t_info *info)
{
	info->r = 0;
	info->g = 0;
	info->b = 0;
	info->r2 = 0;
	info->g2 = 0;
	info->b2 = 0;
}

void    ft_init_info(t_info *info)
{
	
	info->sprites.sprites_buff = ft_calloc(info->width, sizeof(double *));
	info->moveSpeed = 0.03;
	info->rotSpeed = 0.03;
	info->rgb_floor = create_rgb(info->flagF[0], info->flagF[1], info->flagF[2]);
	info->rgb_ceiling = create_rgb(info->flagC[0], info->flagC[1], info->flagC[2]);
}

void	init_play_pos(t_info *info)
{
	if (info->direction == 'N' || info->direction == 'S')
		init_south_north(info);
	else if (info->direction == 'W' || info->direction == 'E')
		init_west_east(info);
}

void	init_south_north(t_info *info)
{
	if (info->direction == 'N')
	{
		info->dirX = -1;
		info->dirY = 0.0;
		info->planeX = 0.0;
		info->planeY = 0.66;
	}
	else if (info->direction == 'S')
	{
		info->dirX = 1;
		info->dirY = 0.0;
		info->planeX = 0.0;
		info->planeY = -0.66;
	}
}

void	init_west_east(t_info *info)
{
	if (info->direction == 'W')
	{
		info->dirX = 0.0;
		info->dirY = -1;
		info->planeX = -0.66;
		info->planeY = 0.0;
	}
	else if (info->direction == 'E')
	{
		info->dirX = 0.0;
		info->dirY = 1;
		info->planeX = 0.66;
		info->planeY = 0.0;
	}
}