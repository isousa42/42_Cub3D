#include "cub3d.h"

void	init_key(t_info *info)
{
	info->keys.key_w = 0;
	info->keys.key_s = 0;
	info->keys.key_a = 0;
	info->keys.key_d = 0;
	info->keys.key_esc = 0;
}

int	key_release(int keycode, t_info *info)
{
	if (keycode == KEY_A)
		info->keys.key_a = 0;
	if (keycode == KEY_W)
		info->keys.key_w = 0;
	if (keycode == KEY_S)
		info->keys.key_s = 0;
	if (keycode == KEY_D)
		info->keys.key_d = 0;
	if (keycode == KEY_ESC)
		info->keys.key_esc = 0;
	return (0);
}

int	key_press(int keycode, t_info *info)
{
	if (keycode == KEY_A)
		info->keys.key_a = 1;
	if (keycode == KEY_W)
		info->keys.key_w = 1;
	if (keycode == KEY_S)
		info->keys.key_s = 1;
	if (keycode == KEY_D)
		info->keys.key_d = 1;
	if (keycode == KEY_ESC)
		info->keys.key_esc = 1;
	return (0);
}

int	key_hook(t_info *info)
{
	if (info->keys.key_w)
	{
		if (info->map[(int)(info->posX + info->dirX * info->moveSpeed)][(int)(info->posY)] == '0')
			info->posX += info->dirX * info->moveSpeed;
		if (info->map[(int)(info->posX)][(int)(info->posY + info->dirY * info->moveSpeed)] == '0')
			info->posY += info->dirY * info->moveSpeed;
	}
	//move backwards if no wall behind you
	if (info->keys.key_s)
	{
		if (info->map[(int)(info->posX - info->dirX * info->moveSpeed)][(int)(info->posY)] == '0')
			info->posX -= info->dirX * info->moveSpeed;
		if (info->map[(int)(info->posX)][(int)(info->posY - info->dirY * info->moveSpeed)] == '0')
			info->posY -= info->dirY * info->moveSpeed;
	}
	//rotate to the right
	if (info->keys.key_d)
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = info->dirX;
		info->dirX = info->dirX * cos(-info->rotSpeed) - info->dirY * sin(-info->rotSpeed);
		info->dirY = oldDirX * sin(-info->rotSpeed) + info->dirY * cos(-info->rotSpeed);
		double oldPlaneX = info->planeX;
		info->planeX = info->planeX * cos(-info->rotSpeed) - info->planeY * sin(-info->rotSpeed);
		info->planeY = oldPlaneX * sin(-info->rotSpeed) + info->planeY * cos(-info->rotSpeed);
	}
	//rotate to the left
	if (info->keys.key_a)
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = info->dirX;
		info->dirX = info->dirX * cos(info->rotSpeed) - info->dirY * sin(info->rotSpeed);
		info->dirY = oldDirX * sin(info->rotSpeed) + info->dirY * cos(info->rotSpeed);
		double oldPlaneX = info->planeX;
		info->planeX = info->planeX * cos(info->rotSpeed) - info->planeY * sin(info->rotSpeed);
		info->planeY = oldPlaneX * sin(info->rotSpeed) + info->planeY * cos(info->rotSpeed);
	}
	if (info->keys.key_esc)
		exit(0);
	return (0);
}