#include "cub3d.h"


void	draw_img(t_info *info)
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			info->img.data[y * width + x] = info->buff[y][x];
		}
	}
	mlx_put_image_to_window(info->mlx, info->win, info->img.img, 0, 0);
}

// FUCTION RC_LOOP - It's the main loop where the raycasting and DDA algorithm happens. It will calculate where to put pixels and ask the draw_line() to draw it in the window

void	rc_loop(t_info *info)
{
	// FLOOR DRAWING
	floor_draw(info);
	// info->rc.j = 0;
	// info->rc.y = 0;
	// while (info->rc.y < height)
	// {
	// 	//rayDir for the leftmost ray (x = 0) and ridhtmost ray (x=w)
	// 	info->rc.rayDirX0 = info->dirX - info->planeX;
	// 	info->rc.rayDirY0 = info->dirY - info->planeY;
	// 	info->rc.rayDirX1 = info->dirX + info->planeX;
	// 	info->rc.rayDirY1 = info->dirY + info->planeY;

	// 	// Current y position compared to the center of the screen (the horizon)
	// 	info->rc.p = info->rc.y - height / 2;

	// 	//Vertical position of the camera
	// 	info->rc.posZ = 0.5 * height;

	// 	//Horizontal distance from the camera to the floor for the current row. 0.5 is the z position exactly in the middle between floor and ceiling
	// 	info->rc.rowDistance = info->rc.posZ / info->rc.p;

	// 	//Calculate the real world step vector we have to add for each x (parallel to camera play). Adding step by step avoids multiplications with a weight in the inner loop
	// 	info->rc.floorStepX = info->rc.rowDistance * (info->rc.rayDirX1 - info->rc.rayDirX0) / width;
	// 	info->rc.floorStepY = info->rc.rowDistance * (info->rc.rayDirY1 - info->rc.rayDirY0) / width;

	// 	//real world coordinates of the leftmost column. This will be updated as we step to the right.
	// 	info->rc.floorX = info->posX + info->rc.rowDistance * info->rc.rayDirX0;
	// 	info->rc.floorY = info->posY + info->rc.rowDistance * info->rc.rayDirY0;

	// 	info->rc.k = 0; // CONFIRM THIS SHIT PLEASE
	// 	while (info->rc.k < width)
	// 	{
	// 		//the cell cordinate is simply got from the integer parts of floorX and floorY
	// 		info->rc.cellX = (int)(info->rc.floorX);
	// 		info->rc.cellY = (int)(info->rc.floorY);

	// 		//get the texture coordinate from the fractional part
	// 		info->rc.tx = (int)(textWidth * (info->rc.floorX - info->rc.cellX)) & (textWidth - 1);
	// 		info->rc.ty = (int)(textHeight * (info->rc.floorY - info->rc.cellY)) & (textHeight - 1);

	// 		info->rc.floorX += info->rc.floorStepX;
	// 		info->rc.floorY += info->rc.floorStepY;

	// 		//choose texture and draw the pixel
	// 		info->rc.floorText = 3;
	// 		info->rc.ceilingText = 6;

	// 		//floor
	// 		info->rc.color = info->texture[info->rc.floorText][textWidth * info->rc.ty + info->rc.tx];
	// 		info->rc.color = (info->rc.color >> 1) & 8355711; //make a bit darker
	// 		info->buff[info->rc.y][info->rc.k] = info->rc.color;

	// 		//ceiling (symmetrical, at screenHeight - y - 1 instead of y)
	// 		info->rc.color = info->texture[info->rc.ceilingText][textWidth * info->rc.ty + info->rc.tx];
	// 		info->rc.color = (info->rc.color >> 1) & 8355711; //(make a bit darker)

	// 		info->buff[height - info->rc.y - 1][info->rc.k] = info->rc.color;
	// 		info->rc.k++;
	// 	}
	// 	info->rc.y++;
	// }

	// // WALL DRAWING
	info->rc.x = 0;
	while (info->rc.x < width) // 640 is width of window
	{
		info->rc.cameraX = 2 * info->rc.x / (double)width - 1; // 0 = middle, 1 = right, -1 = left
		info->rc.rayDirX = info->dirX + info->planeX * info->rc.cameraX; 
		info->rc.rayDirY = info->dirY + info->planeY * info->rc.cameraX; // Sum of the direction of the player and a part of the plane
		info->rc.mapX = (int)info->posX; 
		info->rc.mapY = (int)info->posY; //the ray starts in the same position as the player
		info->rc.deltaDistX = fabs(1 / info->rc.rayDirX); //Simplified from sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX)
		info->rc.deltaDistY = fabs(1 / info->rc.rayDirY); // Simplified from sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY)

		info->rc.hit = 0; // will be 1 if it hits the wall
	
		if (info->rc.rayDirX < 0)
		{
			info->rc.stepX = -1; // Because Dir is negative
			info->rc.sideDistX = (info->posX - info->rc.mapX) * info->rc.deltaDistX; // the distance ray has to travel from initial position to the next x-side. This formula gives the real Euclidian distance.
		}
		else
		{
			info->rc.stepX = 1;
			info->rc.sideDistX = (info->rc.mapX + 1.0 - info->posX) * info->rc.deltaDistX; //This gives the real Euclidian distance	
		}
		if (info->rc.rayDirY < 0)
		{
			info->rc.stepY = -1;
			info->rc.sideDistY = (info->posY - info->rc.mapY) * info->rc.deltaDistY;
		}
		else
		{
			info->rc.stepY = 1;
			info->rc.sideDistY = (info->rc.mapY + 1.0 - info->posY) * info->rc.deltaDistY;
		}
	// PERFORM DDA ALGORITHM
		while (info->rc.hit == 0)
		{
			//go to next map square
			if (info->rc.sideDistX < info->rc.sideDistY)
			{
				info->rc.sideDistX += info->rc.deltaDistX;
				info->rc.mapX += info->rc.stepX;
				info->rc.side = 0;
			}
			else
			{
				info->rc.sideDistY += info->rc.deltaDistY;
				info->rc.mapY += info->rc.stepY;
				info->rc.side = 1;
			}
			//Check if the ray hits wall
			if (info->map[info->rc.mapX][info->rc.mapY] > 0)
				info->rc.hit = 1;
		}

		//Calculate distance of perpendicular ray (Euclidean distance will give the fisheye effect
		if (info->rc.side == 0)
			info->rc.perpWallDist = (info->rc.mapX - info->posX + (1 - info->rc.stepX) / 2) / info->rc.rayDirX;
		else
			info->rc.perpWallDist = (info->rc.mapY - info->posY + (1 - info->rc.stepY) / 2) / info->rc.rayDirY;
	
		//Calculate height of line to draw
		info->rc.lineHeight = (int)(height / info->rc.perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		info->rc.drawStart = -info->rc.lineHeight / 2 + height / 2;
		if (info->rc.drawStart < 0)
			info->rc.drawStart = 0;
		info->rc.drawEnd = info->rc.lineHeight / 2 + height / 2;
		if (info->rc.drawEnd >= height)
			info->rc.drawEnd = height - 1;
		
		// TEXTURING CALCULATIONS
		
		info->rc.textNum = info->map[info->rc.mapX][info->rc.mapY] - 1; // this variable is the value of the current map square minus 1, because there is the texture zero, but in the map the 0 has no texture. To be able to use the texture number zero, we need to subtract 1.

		//The value wallX represents the exact value where the wall was hit. This is needed to know which x-coordinate of the texture we have to use. 
		//This is calculated by first calculating the exact x and y coordinate in the world and then subtrating the integer value of the wall. 
		//Even if it is called wallX, it's actually an y-coordinate of the wall if side == 1, but it's always the x-coordinate of the texture.
		if (info->rc.side == 0)
			info->rc.wallX = info->posY + info->rc.perpWallDist * info->rc.rayDirY;
		else
			info->rc.wallX = info->posX + info->rc.perpWallDist * info->rc.rayDirX;
		info->rc.wallX -= floor(info->rc.wallX);

		//X-coordinate of the texture, based on wallX
		info->rc.textX = (int)(info->rc.wallX * (double)textWidth);
		if (info->rc.side == 0 && info->rc.rayDirX > 0)
			info->rc.textX = textWidth - info->rc.textX - 1;
		if (info->rc.side == 1 && info->rc.rayDirY < 0)
			info->rc.textX = textWidth - info->rc.textX - 1;
		
		//How much to increase the texture coordinate perscreen pixel
		info->rc.step = 1.0 * textHeight / info->rc.lineHeight;
		// Starting texture coordinate
		info->rc.textPos = (info->rc.drawStart - height / 2 + info->rc.lineHeight / 2) * info->rc.step;
		info->rc.y = info->rc.drawStart;
		while (info->rc.y < info->rc.drawEnd)
		{
			//Cast the texture coordinate to integer and mask with (textHeight - 1) in case of overflow
			info->rc.textY = (int)info->rc.textPos & (textHeight - 1);
			info->rc.textPos += info->rc.step;
			info->rc.color = info->texture[info->rc.textNum][textHeight * info->rc.textY + info->rc.textX];
			//make color darker for y-sides: R,G,B byte each divided through two with a shift and an and
			if (info->rc.side == 1)
				info->rc.color = (info->rc.color >> 1) & 8355711;
			info->buff[info->rc.y][info->rc.x] = info->rc.color;
			info->rc.y++;
		}

		// FLOOR DRAWING (vertical version, directly after drawing the vertical wall stripe for the current c)
		// x and y position of the floor texel at the bottom of the wall
		// 4 different wall directions possible
		if (info->rc.side == 0 && info->rc.rayDirX > 0)
		{
			info->rc.floorXWall = info->rc.mapX;
			info->rc.floorYWall = info->rc.mapY + info->rc.wallX;
		}
		else if (info->rc.side == 0 && info->rc.rayDirX < 0)
		{
			info->rc.floorXWall = info->rc.mapX + 1.0;
			info->rc.floorYWall = info->rc.mapY + info->rc.wallX;
		}
		else if (info->rc.side == 1 && info->rc.rayDirY > 0)
		{
			info->rc.floorXWall = info->rc.mapX + info->rc.wallX;
			info->rc.floorYWall = info->rc.mapY;
		}
		else
		{
			info->rc.floorXWall = info->rc.mapX + info->rc.wallX;
			info->rc.floorYWall = info->rc.mapY + 1.0;
		}

		info->rc.distWall = info->rc.perpWallDist;
		info->rc.distPlayer = 0.0;

		if (info->rc.drawEnd < 0)
			info->rc.drawEnd = height; //becomes < 0 whetn the integer overflows
		//Draw the floor from drawEnd to the bottom of the screen
		info->rc.y = info->rc.drawEnd + 1;
		while (info->rc.y < height)
		{
			info->rc.currentDist = height / (2.0 * info->rc.y - height); // you could make a small lookup table for this instead
			info->rc.weight = (info->rc.currentDist - info->rc.distPlayer) / (info->rc.distWall - info->rc.distPlayer);
			info->rc.currentFloorX = info->rc.weight * info->rc.floorXWall + (1.0 - info->rc.weight) * info->posX;
			info->rc.currentFloorY = info->rc.weight * info->rc.floorYWall + (1.0 - info->rc.weight) * info->posY;

			info->rc.floorTextX = (int)(info->rc.currentFloorX * textWidth) % textWidth;
			info->rc.floorTextY = (int)(info->rc.currentFloorY * textHeight) % textHeight;

			info->rc.checkerBoardPattern = ((int)(info->rc.currentFloorX) + (int)(info->rc.currentFloorY)) % 2;
			if (info->rc.checkerBoardPattern == 0)
				info->rc.floorTexture = 3;
			else
				info->rc.floorTexture = 4;

			//floor
			info->buff[info->rc.y][info->rc.x] = (info->texture[info->rc.floorTexture][textWidth * info->rc.floorTextY + info->rc.floorTextX] >> 1) & 8355711;

			// ceiling (symmetrical)
			info->buff[height - info->rc.y][info->rc.x] = info->texture[6] [textWidth * info->rc.floorTextY + info->rc.floorTextX];
			info->rc.y++;
		}
		info->rc.x++;
	}
}

int	first_loop(t_info *info)
{
	rc_loop(info);
	draw_img(info);
	key_hook(info);

	return (0);
}

int main()
{
	t_info info;
	info.mlx = mlx_init();
	init_map(&info);

	//initialize the variables of the info struct
	ft_init_info(&info);
	
	//Create buff and textures
	if (ft_handle_text(&info) != 0)
		return (-1);

	info.win = mlx_new_window(info.mlx, width, height, "mlx");

	// Creating the image
	info.img.img = mlx_new_image(info.mlx, width, height);
	info.img.data = (int *)mlx_get_data_addr(info.img.img, &info.img.bpp, &info.img.size, &info.img.endian);


	mlx_loop_hook(info.mlx, &first_loop, &info);
	mlx_hook(info.win, X_EVENT_KEY_PRESS, 0, &key_press, &info);
	mlx_hook(info.win, 3, 0, &key_release, &info);

    mlx_loop(info.mlx);		
}
