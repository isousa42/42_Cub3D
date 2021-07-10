#include "cub3d.h"

void	init_key(t_info *info)
{
	info->keys.key_w = 0;
	info->keys.key_s = 0;
	info->keys.key_a = 0;
	info->keys.key_d = 0;
	info->keys.key_esc = 0;
	info->keys.key_right = 0;
	info->keys.key_left = 0;
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
	if (keycode == KEY_RIGHT)
		info->keys.key_right = 0;
	if (keycode == KEY_LEFT)
		info->keys.key_left = 0;
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
	if (keycode == KEY_RIGHT)
		info->keys.key_right = 1;
	if (keycode == KEY_LEFT)
		info->keys.key_left = 1;
	return (0);
}
