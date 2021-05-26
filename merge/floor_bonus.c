#include "cub3d.h"

#include "cub3d.h"

void	floor_init(t_info *info)
{
	double	norm;

	info->rc.rayDirX0 = info->dirX - info->planeX;
	info->rc.rayDirY0 = info->dirY - info->planeY;
	info->rc.rayDirX1 = info->dirX + info->planeX;
	info->rc.rayDirY1 = info->dirY + info->planeY;
	info->rc.p = info->rc.y - info->height / 2;
	info->rc.posZ = 0.5 * info->width;
	info->rc.rowDistance = info->rc.posZ / info->rc.p;
	norm = info->rc.rayDirX1 - info->rc.rayDirX0;
	info->rc.floorStepX = info->rc.rowDistance * norm / info->width;
	norm = info->rc.rayDirY1 - info->rc.rayDirY0;
	info->rc.floorStepY = info->rc.rowDistance * norm / info->width;
	info->rc.floorX = info->posX + info->rc.rowDistance * info->rc.rayDirX0;
	info->rc.floorY = info->posY + info->rc.rowDistance * info->rc.rayDirY0;
	info->rc.k = 0;
}

void	floor_calculations(t_info *info)
{
	double	norm;

	info->rc.cellX = (int)(info->rc.floorX);
	info->rc.cellY = (int)(info->rc.floorY);
	norm = info->rc.floorX - info->rc.cellX;
	info->rc.tx = (int)(TEXTWIDTH * norm) & (TEXTWIDTH - 1);
	norm = info->rc.floorY - info->rc.cellY;
	info->rc.ty = (int)(TEXTHEIGHT * norm) & (TEXTHEIGHT - 1);
	info->rc.floorX += info->rc.floorStepX;
	info->rc.floorY += info->rc.floorStepY;
	info->rc.floorText = 6;
	info->rc.ceilingText = 5;
}

void	floor_setup(t_info *info)
{
	int	norm;

	norm = TEXTWIDTH * info->rc.ty + info->rc.tx;
	info->rc.color = info->texture[info->rc.floorText][norm];
	info->rc.color = (info->rc.color >> 1) & 8355711;
	info->buff[info->rc.y][info->rc.k] = info->rc.color;
	norm = TEXTWIDTH * info->rc.ty + info->rc.tx;
	info->rc.color = info->texture[info->rc.ceilingText][norm];
	info->rc.color = (info->rc.color >> 1) & 8355711;
	info->buff[info->height - info->rc.y - 1][info->rc.k] = info->rc.color;
}

void	floor_draw(t_info *info)
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
