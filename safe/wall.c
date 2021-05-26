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

void	wall_calc(t_info *info)
{
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
}

void	wall_text(t_info *info)
{
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
}