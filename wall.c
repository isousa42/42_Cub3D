#include "cub3d.h"

void    wall_init(t_info *info)
{
    	info->rc.cameraX = 2 * info->rc.x / (double)width - 1; // 0 = middle, 1 = right, -1 = left
		info->rc.rayDirX = info->dirX + info->planeX * info->rc.cameraX; 
		info->rc.rayDirY = info->dirY + info->planeY * info->rc.cameraX; // Sum of the direction of the player and a part of the plane
		info->rc.mapX = (int)info->posX; 
		info->rc.mapY = (int)info->posY; //the ray starts in the same position as the player
		info->rc.deltaDistX = fabs(1 / info->rc.rayDirX); //Simplified from sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX)
		info->rc.deltaDistY = fabs(1 / info->rc.rayDirY); // Simplified from sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY)

		info->rc.hit = 0; // will be 1 if it hits the wall
}

void    ray_walking(t_info *info)
{
    	if (info->rc.rayDirX < 0)
		{
			info->rc.stepX = -1; // Because Dir is negative
			info->rc.sideDistX = (info->posX - info->rc.mapX) * info->rc.deltaDistX; // the distance ray has to travel from initial position to the next x-side. This formula gives the real Euclidian distance.
		}
		else
		{
			info->rc.stepX = 1;
			info->rc.sideDistX = (info->rc.mapX + 1.0 - info->posX) * info->rc.deltaDistX; //This gives the real Euclidian distance	
		}
		if (info->rc.rayDirY < 0)
		{
			info->rc.stepY = -1;
			info->rc.sideDistY = (info->posY - info->rc.mapY) * info->rc.deltaDistY;
		}
		else
		{
			info->rc.stepY = 1;
			info->rc.sideDistY = (info->rc.mapY + 1.0 - info->posY) * info->rc.deltaDistY;
		}
}

void    dda_algorithm(t_info *info)
{
    while (info->rc.hit == 0)
		{
			//go to next map square
			if (info->rc.sideDistX < info->rc.sideDistY)
			{
				info->rc.sideDistX += info->rc.deltaDistX;
				info->rc.mapX += info->rc.stepX;
				info->rc.side = 0;
			}
			else
			{
				info->rc.sideDistY += info->rc.deltaDistY;
				info->rc.mapY += info->rc.stepY;
				info->rc.side = 1;
			}
			//Check if the ray hits wall
			if (info->map[info->rc.mapX][info->rc.mapY] > 0)
				info->rc.hit = 1;
		}
}