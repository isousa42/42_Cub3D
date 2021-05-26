#include "cub3d.h"

void	sprites_init(t_info *info, double spriteX, double spriteY, int texture)
{
	spriteX = (spriteX + 0.5) - info->posX;
	spriteY = (spriteY + 0.5) - info->posY;
	info->norm = info->planeX * info->dirY - info->dirX * info->planeY;
	info->sprites.inversion = 1.0 / (info->norm);
	info->norm = info->dirY * spriteX - info->dirX * spriteY;
	info->sprites.depthX = info->sprites.inversion * (info->norm);
	info->norm = -info->planeY * spriteX + info->planeX * spriteY;
	info->sprites.depthY = info->sprites.inversion * (info->norm);
	info->norm = 1 + info->sprites.depthX / info->sprites.depthY;
	info->sprites.screenX = (int)((info->width / 2) * (info->norm));
	info->sprites.move = (int)(0.0 / info->sprites.depthY);
	info->norm = info->height / info->sprites.depthY;
	info->sprites.spriteHeight = (int)fabs((info->norm) / 1);
	info->norm = info->height / 2 + info->sprites.move;
	info->sprites.drawStartY = -info->sprites.spriteHeight / 2 + info->norm;
	sprites_cond(info, spriteX, spriteY, texture);
}

void	sprites_cond(t_info *info, double spriteX, double spriteY, int texture)
{
	if (info->sprites.drawStartY <= 0)
		info->sprites.drawStartY = 0;
	info->norm = info->height / 2 + info->sprites.move;
	info->sprites.drawEndY = info->sprites.spriteHeight / 2 + info->norm;
	if (info->sprites.drawEndY >= info->height)
		info->sprites.drawEndY = info->height - 1;
	info->norm = info->height / info->sprites.depthY;
	info->sprites.spriteWidth = (int)fabs((info->norm) / 1);
	info->norm = -info->sprites.spriteWidth / 2 + info->sprites.screenX;
	info->sprites.drawStartX = info->norm;
	if (info->sprites.drawStartX < 0)
		info->sprites.drawStartX = 0;
	info->norm = info->sprites.spriteWidth / 2;
	info->sprites.drawEndX = info->norm + info->sprites.screenX;
	if (info->sprites.drawEndX >= info->width)
		info->sprites.drawEndX = info->width - 1;
	info->sprites.sprite = info->sprites.drawStartX;
}

void	print_sprite(t_info *info, int texture, int y)
{
	int	norm3;
	int	norm4;
	int	norm5;

	norm3 = y - info->sprites.move;
	norm4 = info->sprites.spriteHeight * 128;
	norm5 = info->height * 128;
	info->sprites.avoid_overflow = norm3 * 256 - norm5 + norm4;
	norm3 = info->sprites.avoid_overflow * TEXTHEIGHT;
	norm4 = norm3 / info->sprites.spriteHeight;
	info->sprites.textY = norm4 / 256;
	norm5 = TEXTWIDTH * info->sprites.textY + info->sprites.textX;
	info->sprites.sprite_color = info->texture[texture][norm5];
	norm3 = info->sprites.sprite_color;
	if ((info->sprites.sprite_color & 0x00FFFFFF) != 0)
		info->buff[y][info->sprites.sprite] = norm3;
}

void	sprites_draw(t_info *info, double spriteX, double spriteY, int texture)
{
	int	y;
	int	norm3;
	int	norm4;

	sprites_init(info, spriteX, spriteY, texture);
	while (info->sprites.sprite < info->sprites.drawEndX)
	{
		norm3 = (-info->sprites.spriteWidth / 2 + info->sprites.screenX);
		norm4 = info->sprites.sprite - norm3;
		norm3 = (norm4 * TEXTWIDTH / info->sprites.spriteWidth);
		info->sprites.textX = (int)(256 * norm3 / 256);
		norm3 = info->sprites.sprites_buff[info->sprites.sprite];
		if (info->sprites.depthY > 0 && info->sprites.sprite > 0
			&& info->sprites.sprite < info->width
			&& info->sprites.depthY < norm3)
		{
			y = info->sprites.drawStartY;
			while (y < info->sprites.drawEndY)
			{
				print_sprite(info, texture, y);
				y++;
			}
		}
		info->sprites.sprite++;
	}
}
