#include "cub3d.h"

void    ft_init_info(t_info *info)
{
	// int i = 2.5;
	// int j = 2.5;

    // info->posX = 2.5;
	// info->posY = 2.5;

	// Speed of the moves
	info->moveSpeed = 0.03;
	info->rotSpeed = 0.03;

	info->buff = NULL;
	info->texture = NULL;
	
	int i;
	info->sprites.sprites_buff = (double *)malloc(sizeof(double *) * info->width);
	i = 0;
	while(i < info->width)
	{
		info->sprites.sprites_buff[i] = 0;
		i++;
	}

}

// -1 , 0.0 , 0.0, 0.66 - NORTH
// 1, 0.0, 0.0 , -0.66 - SOUTH
// 0.0, -1, -0.66, 0.0 - WEST
// 0.0, 1, 0.66, 0.0 - EAST

void	init_play_pos(t_info *info)
{
	char direction;

	direction = 'W';
	if (direction == 'N')
	{
		//Initial Direction the player is looking
		info->dirX = -1;
		info->dirY = 0.0;

		//Initial FOV
		info->planeX = 0.0;
		info->planeY = 0.66;
	}
	else if (direction == 'S')
	{
		//Initial Direction the player is looking
		info->dirX = 1;
		info->dirY = 0.0;

		//Initial FOV
		info->planeX = 0.0;
		info->planeY = -0.66;
	}
	else if (direction == 'W')
	{
		//Initial Direction the player is looking
		info->dirX = 0.0;
		info->dirY = -1;

		//Initial FOV
		info->planeX = -0.66;
		info->planeY = 0.0;
	}
	else if (direction == 'E')
	{
		//Initial Direction the player is looking
		info->dirX = 0.0;
		info->dirY = 1;

		//Initial FOV
		info->planeX = 0.66;
		info->planeY = 0.0;
	}
}