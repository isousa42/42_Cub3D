#include "cub3d.h"

void    ft_init_info(t_info *info)
{
	int i;
	int j;

    info->posX = 22;
	info->posY = 12;

	//Initial Direction the player is looking
	info->dirX = -1;
	info->dirY = 0.0;

	//Initial FOV
	info->planeX = 0.0;
	info->planeY = 0.66;

	// Speed of the moves
	info->moveSpeed = 0.03;
	info->rotSpeed = 0.03;

	// Width and Height of the window
	

	info->buff = calloc(1024, sizeof(int *));
	i = -1;
	while (++i < 1024)
		info->buff[i] = calloc(1920, sizeof(int *));
	// i = 0;
	// info->buff = (int **)malloc(sizeof(int *) * info->height);
	// while (i < info->height)
	// {
	// 	info->buff[i] = (int *)malloc(sizeof(int *) * info->width);
	// 	i++;
	// }
	// i = 0;
	// j = 0;
	// while (i < info->height)
	// {
	// 	j = 0;
	// 	while (j < info->width)
	// 	{
	// 		info->buff[i][j] = 0;
	// 		j++;
	// 	}
	// 	i++;
	// }
}