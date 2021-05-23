#include "cub3d.h"

void	sprites_init(t_info *info, double spriteX, double spriteY, int texture)
{
	spriteX = (spriteX + 0.5) - info->posX;
	spriteY = (spriteY + 0.5) - info->posY;
	info->sprites.inversion = 1.0 / (info->planeX * info->dirY - info->dirX * info->planeY); 
	info->sprites.depthX = info->sprites.inversion * (info->dirY * spriteX - info->dirX * spriteY);
	info->sprites.depthY = info->sprites.inversion * (-info->planeY * spriteX + info->planeX * spriteY); 
	info->sprites.screenX = (int)((info->width / 2) * (1 + info->sprites.depthX / info->sprites.depthY));
	info->sprites.move = (int)(0.0 / info->sprites.depthY);
	info->sprites.spriteHeight = (int)fabs((info->height / info->sprites.depthY) / 1);
	info->sprites.drawStartY = -info->sprites.spriteHeight / 2 + info->height / 2 + info->sprites.move;
	if(info->sprites.drawStartY <= 0) 
		info->sprites.drawStartY = 0;
	info->sprites.drawEndY = info->sprites.spriteHeight / 2 + info->height / 2 + info->sprites.move;
	if(info->sprites.drawEndY >= info->height) 
		info->sprites.drawEndY = info->height - 1;
	info->sprites.spriteWidth = (int)fabs((info->height / info->sprites.depthY) / 1);
	info->sprites.drawStartX = -info->sprites.spriteWidth / 2 + info->sprites.screenX;
	if(info->sprites.drawStartX < 0) 
		info->sprites.drawStartX = 0;
	info->sprites.drawEndX = info->sprites.spriteWidth / 2 + info->sprites.screenX;
	if(info->sprites.drawEndX >= info->width) 
		info->sprites.drawEndX = info->width - 1;
	info->sprites.sprite = info->sprites.drawStartX;
}

void	sprites_draw(t_info *info, double spriteX, double spriteY, int texture)
{
	int y;

	sprites_init(info, spriteX, spriteY, texture);
	while (info->sprites.sprite < info->sprites.drawEndX)
	{
		info->sprites.textX = (int)((256 * (info->sprites.sprite - (-info->sprites.spriteWidth / 2 + info->sprites.screenX)) * textWidth / info->sprites.spriteWidth) / 256);
		if(info->sprites.depthY > 0 && info->sprites.sprite > 0 && info->sprites.sprite < info->width && info->sprites.depthY < info->sprites.sprites_buff[info->sprites.sprite])
		{
			y = info->sprites.drawStartY;
			while (y < info->sprites.drawEndY)
			{
				info->sprites.avoid_overflow = (y - info->sprites.move) * 256 - info->height * 128 + info->sprites.spriteHeight * 128; 
				info->sprites.textY = ((info->sprites.avoid_overflow * textHeight) / info->sprites.spriteHeight) / 256;
				info->sprites.sprite_color = info->texture[texture][textWidth * info->sprites.textY + info->sprites.textX];
				if((info->sprites.sprite_color & 0x00FFFFFF) != 0) 
					info->buff[y][info->sprites.sprite] = info->sprites.sprite_color;
				y++;
			}
		}
		info->sprites.sprite++;
	}
}