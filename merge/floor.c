#include "cub3d.h"

int		create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

void	floor_init(t_info *info)
{
	//rayDir for the leftmost ray (x = 0) and ridhtmost ray (x=w)
	info->rc.rayDirX0 = info->dirX - info->planeX;
	info->rc.rayDirY0 = info->dirY - info->planeY;
	info->rc.rayDirX1 = info->dirX + info->planeX;
	info->rc.rayDirY1 = info->dirY + info->planeY;

	// Current y position compared to the center of the screen (the horizon)
	info->rc.p = info->rc.y - info->height / 2;

	//Vertical position of the camera
	info->rc.posZ = 0.5 * info->height;

	//Horizontal distance from the camera to the floor for the current row. 0.5 is the z position exactly in the middle between floor and ceiling
	info->rc.rowDistance = info->rc.posZ / info->rc.p;

	//Calculate the real world step vector we have to add for each x (parallel to camera play). Adding step by step avoids multiplications with a weight in the inner loop
	info->rc.floorStepX = info->rc.rowDistance * (info->rc.rayDirX1 - info->rc.rayDirX0) / info->width;
	info->rc.floorStepY = info->rc.rowDistance * (info->rc.rayDirY1 - info->rc.rayDirY0) / info->width;

	//real world coordinates of the leftmost column. This will be updated as we step to the right.
	info->rc.floorX = info->posX + info->rc.rowDistance * info->rc.rayDirX0;
	info->rc.floorY = info->posY + info->rc.rowDistance * info->rc.rayDirY0;

	info->rc.k = 0; // CONFIRM THIS SHIT PLEASE
}

void	floor_calculations(t_info *info)
{
	//the cell cordinate is simply got from the integer parts of floorX and floorY
	info->rc.cellX = (int)(info->rc.floorX);
	info->rc.cellY = (int)(info->rc.floorY);

	//get the texture coordinate from the fractional part
	info->rc.tx = (int)(textWidth * (info->rc.floorX - info->rc.cellX)) & (textWidth - 1);
	info->rc.ty = (int)(textHeight * (info->rc.floorY - info->rc.cellY)) & (textHeight - 1);

	info->rc.floorX += info->rc.floorStepX;
	info->rc.floorY += info->rc.floorStepY;

	//choose texture and draw the pixel
	info->rc.floorText = 3;
	info->rc.ceilingText = 6;
}

void	floor_setup(t_info *info)  // CHANGES HERE FOR THE MANDATORY PART!!!!!
{
	//floor
	// info->rc.color = info->texture[info->rc.floorText][textWidth * info->rc.ty + info->rc.tx];
	// info->rc.color = (info->rc.color >> 1) & 8355711; //make a bit darker

	info->buff[info->rc.y][info->rc.k] = info->rgb_floor; // CHANGED HERE FOR 255 = BLUE

	//ceiling (symmetrical, at screenHeight - y - 1 instead of y)
	// info->rc.color = info->texture[info->rc.ceilingText][textWidth * info->rc.ty + info->rc.tx];
	// info->rc.color = (info->rc.color >> 1) & 8355711; //(make a bit darker)

	info->buff[info->height - info->rc.y - 1][info->rc.k] = info->rgb_ceiling; // CHANGED HERE FOR 0 = BLACK
}

void    floor_draw(t_info *info)
{
	info->rc.y = 0;
	while (info->rc.y < info->height)
	{
		floor_init(info);
		while (info->rc.k < info->width)
		{
			floor_calculations(info);
			floor_setup(info);
			info->rc.k++;
		}
		info->rc.y++;
	}
}