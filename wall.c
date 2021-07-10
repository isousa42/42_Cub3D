#include "cub3d.h"

void	wall_init(t_info *info)
{
	info->rc.cameraX = 2 * info->rc.x / (double)info->width - 1;
	info->rc.rayDirX = info->dirX + info->planeX * info->rc.cameraX;
	info->rc.rayDirY = info->dirY + info->planeY * info->rc.cameraX;
	info->rc.mapX = (int)info->posX;
	info->rc.mapY = (int)info->posY;
	info->rc.dDX = fabs(1 / info->rc.rayDirX);
	info->rc.dDY = fabs(1 / info->rc.rayDirY);
	info->rc.hit = 0;
}

void	ray_walking(t_info *info)
{
	if (info->rc.rayDirX < 0)
	{
		info->rc.stepX = -1;
		info->rc.sideDistX = (info->posX - info->rc.mapX) * info->rc.dDX;
	}
	else
	{
		info->rc.stepX = 1;
		info->rc.sideDistX = (info->rc.mapX + 1.0 - info->posX) * info->rc.dDX;
	}
	if (info->rc.rayDirY < 0)
	{
		info->rc.stepY = -1;
		info->rc.sideDistY = (info->posY - info->rc.mapY) * info->rc.dDY;
	}
	else
	{
		info->rc.stepY = 1;
		info->rc.sideDistY = (info->rc.mapY + 1.0 - info->posY) * info->rc.dDY;
	}
}

void	dda_algorithm(t_info *info)
{
	while (info->rc.hit == 0)
	{
		if (info->rc.sideDistX < info->rc.sideDistY)
		{
			info->rc.sideDistX += info->rc.dDX;
			info->rc.mapX += info->rc.stepX;
			info->rc.side = 0;
			if (info->rc.stepX == 1)
				info->rc.side = 0;
			else if (info->rc.stepX == -1)
				info->rc.side = 1;
		}
		else
		{
			info->rc.sideDistY += info->rc.dDY;
			info->rc.mapY += info->rc.stepY;
			info->rc.side = 1;
			if (info->rc.stepY == 1)
				info->rc.side = 2;
			else if (info->rc.stepY == -1)
				info->rc.side = 3;
		}
		if (info->map[info->rc.mapX][info->rc.mapY] == '1')
			info->rc.hit = 1;
	}
}

void	wall_calc(t_info *info)
{
	double	norm;
	double	norm2;

	norm = (info->rc.mapX - info->posX + (1 - info->rc.stepX) / 2);
	norm2 = (info->rc.mapY - info->posY + (1 - info->rc.stepY) / 2);
	if (info->rc.side == 0 || info->rc.side == 1)
		info->rc.perpWallDist = norm / info->rc.rayDirX;
	else
		info->rc.perpWallDist = norm2 / info->rc.rayDirY;
	info->rc.lineHeight = (int)(info->height / info->rc.perpWallDist);
	info->rc.drawStart = -info->rc.lineHeight / 2 + info->height / 2;
	if (info->rc.drawStart < 0)
		info->rc.drawStart = 0;
	info->rc.drawEnd = info->rc.lineHeight / 2 + info->height / 2;
	if (info->rc.drawEnd >= info->height)
		info->rc.drawEnd = info->height - 1;
}

void	wall_text(t_info *info)
{
	double	norm;

	norm = (info->rc.drawStart - info->height / 2 + info->rc.lineHeight / 2);
	if (info->rc.side == 0 || info->rc.side == 1)
		info->rc.wallX = info->posY + info->rc.perpWallDist * info->rc.rayDirY;
	else
		info->rc.wallX = info->posX + info->rc.perpWallDist * info->rc.rayDirX;
	info->rc.wallX -= floor(info->rc.wallX);
	info->rc.textX = (int)(info->rc.wallX * (double)TEXTWIDTH);
	if (info->rc.side == 0 && info->rc.rayDirX > 0)
		info->rc.textX = TEXTWIDTH - info->rc.textX - 1;
	if (info->rc.side == 1 && info->rc.rayDirY < 0)
		info->rc.textX = TEXTWIDTH - info->rc.textX - 1;
	info->rc.step = 1.0 * TEXTHEIGHT / info->rc.lineHeight;
	info->rc.textPos = norm * info->rc.step;
	info->rc.y = info->rc.drawStart;
}
