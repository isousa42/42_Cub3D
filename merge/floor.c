#include "cub3d.h"

void	floor_init(t_info *info)
{
	info->rc.rayDirX0 = info->dirX - info->planeX;
	info->rc.rayDirY0 = info->dirY - info->planeY;
	info->rc.rayDirX1 = info->dirX + info->planeX;
	info->rc.rayDirY1 = info->dirY + info->planeY;
	info->rc.p = info->rc.y - info->height / 2;
	info->rc.posZ = 0.5 * info->height;
	info->rc.rowDistance = info->rc.posZ / info->rc.p;
	info->rc.floorStepX = info->rc.rowDistance * (info->rc.rayDirX1 - info->rc.rayDirX0) / info->width;
	info->rc.floorStepY = info->rc.rowDistance * (info->rc.rayDirY1 - info->rc.rayDirY0) / info->width;
	info->rc.floorX = info->posX + info->rc.rowDistance * info->rc.rayDirX0;
	info->rc.floorY = info->posY + info->rc.rowDistance * info->rc.rayDirY0;
	info->rc.k = 0;
}

void	floor_calculations(t_info *info)
{
	info->rc.cellX = (int)(info->rc.floorX);
	info->rc.cellY = (int)(info->rc.floorY);
	info->rc.tx = (int)(textWidth * (info->rc.floorX - info->rc.cellX)) & (textWidth - 1);
	info->rc.ty = (int)(textHeight * (info->rc.floorY - info->rc.cellY)) & (textHeight - 1);
	info->rc.floorX += info->rc.floorStepX;
	info->rc.floorY += info->rc.floorStepY;
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
			info->buff[info->rc.y][info->rc.k] = info->rgb_floor; 
			info->buff[info->height - info->rc.y - 1][info->rc.k] = info->rgb_ceiling;
			info->rc.k++;
		}
		info->rc.y++;
	}
}