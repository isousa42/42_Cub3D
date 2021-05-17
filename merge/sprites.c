#include "cub3d.h"

void	sprites_draw(t_info *info, double spriteX, double spriteY, int texture)
{
	//translate sprite position to relative to camera
		spriteX = (spriteX + 0.5) - info->posX;
		spriteY = (spriteY + 0.5) - info->posY;

		//transform sprite with the inverse camera matrix
		// [ planeX   dirX ] -1                                       [ dirY      -dirX ]
		// [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
		// [ planeY   dirY ]                                          [ -planeY  planeX ]

		info->sprites.inversion = 1.0 / (info->planeX * info->dirY - info->dirX * info->planeY); //required for correct matrix multiplication

		info->sprites.depthX = info->sprites.inversion * (info->dirY * spriteX - info->dirX * spriteY);
		info->sprites.depthY = info->sprites.inversion * (-info->planeY * spriteX + info->planeX * spriteY); //this is actually the depth inside the screen, that what Z is in 3D, the distance of sprite to player, matching sqrt(spriteDistance[i])

		info->sprites.screenX = (int)((info->width / 2) * (1 + info->sprites.depthX / info->sprites.depthY));

		//parameters for scaling and moving the sprites
		info->sprites.move = (int)(0.0 / info->sprites.depthY);

		//calculate height of the sprite on screen
		info->sprites.spriteHeight = (int)fabs((info->height / info->sprites.depthY) / 1); //using "info->sprites.depthY" instead of the real distance prevents fisheye
		//calculate lowest and highest pixel to fill in current stripe
		info->sprites.drawStartY = -info->sprites.spriteHeight / 2 + info->height / 2 + info->sprites.move;
		if(info->sprites.drawStartY <= 0) 
			info->sprites.drawStartY = 0;
		info->sprites.drawEndY = info->sprites.spriteHeight / 2 + info->height / 2 + info->sprites.move;
		if(info->sprites.drawEndY >= info->height) 
			info->sprites.drawEndY = info->height - 1;

		//calculate width of the sprite
		info->sprites.spriteWidth = (int)fabs((info->height / info->sprites.depthY) / 1);
		info->sprites.drawStartX = -info->sprites.spriteWidth / 2 + info->sprites.screenX;
		if(info->sprites.drawStartX < 0) info->sprites.drawStartX = 0;
		info->sprites.drawEndX = info->sprites.spriteWidth / 2 + info->sprites.screenX;
		if(info->sprites.drawEndX >= info->width) info->sprites.drawEndX = info->width - 1;

		//loop through every vertical stripe of the sprite on screen
		for(info->sprites.sprite = info->sprites.drawStartX; info->sprites.sprite < info->sprites.drawEndX; info->sprites.sprite++)
		{
			info->sprites.textX = (int)((256 * (info->sprites.sprite - (-info->sprites.spriteWidth / 2 + info->sprites.screenX)) * textWidth / info->sprites.spriteWidth) / 256);
			//the conditions in the if are:
			//1) it's in front of camera plane so you don't see things behind you
			//2) it's on the screen (left)
			//3) it's on the screen (right)
			//4) ZBuffer, with perpendicular distance
			if(info->sprites.depthY > 0 && info->sprites.sprite > 0 && info->sprites.sprite < info->width && info->sprites.depthY < info->sprites.sprites_buff[info->sprites.sprite])
			for(int y = info->sprites.drawStartY; y < info->sprites.drawEndY; y++) //for every pixel of the current info->sprites.sprite
			{
				info->sprites.avoid_overflow = (y - info->sprites.move) * 256 - info->height * 128 + info->sprites.spriteHeight * 128; //256 and 128 factors to avoid floats
				info->sprites.textY = ((info->sprites.avoid_overflow * textHeight) / info->sprites.spriteHeight) / 256;
				info->sprites.sprite_color = info->texture[texture][textWidth * info->sprites.textY + info->sprites.textX]; //get current info->sprites.sprite_color from the texture
				if((info->sprites.sprite_color & 0x00FFFFFF) != 0) info->buff[y][info->sprites.sprite] = info->sprites.sprite_color; //paint pixel if it isn't black, black is the invisible color
			}
		}
}