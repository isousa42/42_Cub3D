#include "cub3d.h"

void	handle_keys(t_info *info, int keys)
{
	double	oldDirX;
	double	oldPlaneX;
	double	norm;
	double	norm2;

	if (keys == 1)
	{
		norm = -info->rotSpeed;
		oldDirX = info->dirX;
		info->dirX = info->dirX * cos(norm) - info->dirY * sin(norm);
		info->dirY = oldDirX * sin(norm) + info->dirY * cos(norm);
		oldPlaneX = info->planeX;
		info->planeX = info->planeX * cos(norm) - info->planeY * sin(norm);
		info->planeY = oldPlaneX * sin(norm) + info->planeY * cos(norm);
	}
	if (keys == 2)
	{
		norm2 = info->rotSpeed;
		oldDirX = info->dirX;
		info->dirX = info->dirX * cos(norm2) - info->dirY * sin(norm2);
		info->dirY = oldDirX * sin(norm2) + info->dirY * cos(norm2);
		oldPlaneX = info->planeX;
		info->planeX = info->planeX * cos(norm2) - info->planeY * sin(norm2);
		info->planeY = oldPlaneX * sin(norm2) + info->planeY * cos(norm2);
	}
}

void	handle_keys_2(t_info *info, int keys)
{
	if (keys == 3)
	{
		if (info->keys.key_w)
		{
			info->norm2 = info->posX + info->dirX * info->moveSpeed;
			if (info->map[(int)(info->norm2)][(int)(info->posY)] == '0')
				info->posX += info->dirX * info->moveSpeed;
			info->norm2 = info->posY + info->dirY * info->moveSpeed;
			if (info->map[(int)(info->posX)][(int)(info->norm2)] == '0')
				info->posY += info->dirY * info->moveSpeed;
		}
	}
	if (keys == 4)
	{
		if (info->keys.key_s)
		{
			info->norm2 = info->posX - info->dirX * info->moveSpeed;
			if (info->map[(int)(info->norm2)][(int)(info->posY)] == '0')
				info->posX -= info->dirX * info->moveSpeed;
			info->norm2 = info->posY - info->dirY * info->moveSpeed;
			if (info->map[(int)(info->posX)][(int)(info->norm2)] == '0')
				info->posY -= info->dirY * info->moveSpeed;
		}
	}
}

int	key_hook(t_info *info)
{
	if (info->keys.key_w)
		handle_keys_2(info, 3);
	if (info->keys.key_s)
		handle_keys_2(info, 4);
	if (info->keys.key_d || info->keys.key_right)
		handle_keys(info, 1);
	if (info->keys.key_a || info->keys.key_left)
		handle_keys(info, 2);
	if (info->keys.key_esc)
		exit(0);
	return (0);
}
