#include "cub3d.h"

void    ft_init_info(t_info *info)
{
	int i = 2;
	int j = 2;

    info->posX = i;
	info->posY = j;

	// Speed of the moves
	info->moveSpeed = 0.03;
	info->rotSpeed = 0.03;

	// Width and Height of the window
	info->width = 1000;
	info->height = 1000;
	info->buff = NULL;
	info->texture = NULL;


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