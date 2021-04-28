#include "cub3d.h"

void    ft_init_info(t_info *info)
{
    info->posX = 22;
	info->posY = 12;

	//Initial Direction the player is looking
	info->dirX = -1;
	info->dirY = 0.0;

	//Initial FOV
	info->planeX = 0.0;
	info->planeY = 0.66;

	// Speed of the moves
	info->moveSpeed = 0.15;
	info->rotSpeed = 0.15;
}