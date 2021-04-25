#include "mlx.h"
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define mapWidth 24
#define mapHeight 24
#define width 640
#define height 480
#define textwidth 64
#define textheight 64

#define KEY_W 13
#define KEY_S 1
#define KEY_A 0
#define KEY_D 2

typedef struct s_info
{
	void *mlx;
	void *win;
	t_image img;
	int	buf[width][height];
	int	**texture;
	double posX;
	double posY;
	double dirX;
	double dirY;
	double planeX;
	double planeY;
	double time;
	double oldTime;
	double moveSpeed;
	double rotSpeed;
	double oldDirX;
	double oldPlaneX;
}		t_info;

typedef struct s_image
{
	void	*img;
	int	*data;
	int	size;
	int	bpp;
	int	endian;
	int	img_width;
	int	img_height;
}		t_image

int map[mapWidth][mapHeight]=
{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  	{1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,1,0,1,0,1,0,0,0,1},
  	{1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
  	{1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,0,1},
  	{1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
  	{1,0,0,0,0,0,1,1,0,1,1,0,0,0,0,1,0,1,0,1,0,0,0,1},
  	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  	{1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  	{1,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  	{1,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  	{1,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

/*
// FUNTION DRAW_LINE - Draws the vertical lines in the window after calculation

void	draw_line(t_info *info, int x, int start, int end, int color)
{

	while(start <= end)
	{
		mlx_pixel_put(info->mlx, info->win, x, start, color);
		start++;
	}
}
*/

// FUNCTION draw_img() is going to draw the image of the walls and the upload this image to the window
void	draw_img(t_info *info)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (x < height)
	{
		while (y < width)
		{
			info->img.data[x * width * y] = info->buff[x][y];
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(info->mlx, info->wind, info->img.img, 0, 0);
}

// FUCTION RC_LOOP - It's the main loop where the raycasting and DDA algorithm happens. It will calculate where to put pixels and ask the draw_line() to draw it in the window

void	rc_loop(t_info *info)
{
	// FLOOR DRAWING
	int j;
	float rayDirX0;
	float rayDirY0;
	float rayDirX0;
	float rayDirX1;
	int p;
	float posZ;
	float rowDistance;
	float floorStepX;
	float floorStepY;
	float floorX;
	float floorY;
	int k;
	int cellX;
	int cellY;
	int tx;
	int ty;
	int floorText;
	int ceilingText;
	int colorFC;

	j = 0;
	while (y < height)
	{
		//rayDir for the leftmost ray (x = 0) and ridhtmost ray (x=w)
		rayDirX0 = info->dirX - info->planeX;
		rayDirY0 = info->dirY - info->planeY;
		rayDirX1 = info->dirX - info->planeX;
		rayDirY1 = info->dirY + info->planeY;

		// Current y position compared to the center of the screen (the horizon)
		p = y - height / 2;

		//Vertical position of the camera
		posZ = 0.5 * height;

		//Horizontal distance from the camera to the floor for the current row. 0.5 is the z position exactly in the middle between floor and ceiling
		rowDistance = posZ / p;

		//Calculate the real world step vector we have to add for each x (parallel to camera play). Adding step by step avoids multiplications with a weight in the inner loop
		floorStepX = rowDistance * (rayDirX1 - rayDirX0) / width;
		floorStepY = rowDistance * (rayDirY1 - rayDirY0) / width;

		//real world coordinates of the leftmost column. This will be updated as we step to the right.
		floorX = info->posX + rowDistance * rayDirX0;
		floorY = info->posY + rowDistance * rayDirY0;

		int k = 0;
		while (k < width)
		{
			//the cell cordinate is simply got from the integer parts of floorX and floorY
			cellX = (int)(floorX);
			cellY = (int)(floorY);

			//get the texture coordinate from the fractional part
			tx = (int)(textWidth * (floorX - cellX)) & (textWidth - 1);
			ty = (int)(textHeight * (floorY - cellY)) & (textHeight - 1);

			floorX += floorStepX;
			floorY += floorStepY;

			//choose texture and draw the pixel
			floorText = 3;
			ceilingText = 6;

			//floor
			color = info->texture[floorText][textWidth * ty + tx];
			color = (color >> 1) & 8355711; //make a bit darker
			info[buf[x][y] = color;

			//ceiling (symmetrical, at screenHeight - y - 1 instead of y)
			color = info->texture[ceilingText][textWidth * ty + tx];
			color = (color >> 1) & 8355711; (make a bit darker

			info->buff[height - y - 1][y] = color;



	// WALL DRAWING
	int x; //columns of the window

	double cameraX; // x-coordinate on the camera plane that the current x-coordinate of the screen represents.

	double rayDirX; // Direction of the ray on X
	double rayDirY; // Direction of the ray on Y
	
	int mapX; // Represents the current square the ray is
	int mapY; // This too

	double sideDistX;
	double sideDistY;

	double deltaDistX; //Distance the ray has to travel to go to the next x-coordinate
	double deltaDistY; //Distance the ray has to travel to go to the next y-coordinate
	double perpWallDist;

	int stepX;
	int stepY;

	int hit; //will tell if the ray hit a wall
	int side; //will tell if the ray hit a NS or EW wall

	//Variables used on calculation to draw
	int lineHeight;
	int drawStart;
	int drawEnd;
	int color;

	//Variables for texture calculations
	int textNum;
	double wallX;
	int textX;
	double step;
	double textPos;
	int i;
	int textY;

	x = 0;
	while (x < width) // 640 is width of window
	{
		cameraX = 2 * x / (double)width - 1; // 0 = middle, 1 = right, -1 = left
		rayDirX = info->dirX + info->planeX * cameraX; 
		rayDirY = info->dirY + info->planeY * cameraX; // Sum of the direction of the player and a part of the plane
		mapX = (int)info->posX; 
		mapY = (int)info->posY; //the ray starts in the same position as the player
		deltaDistX = fabs(1 / rayDirX); //Simplified from sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX)
		deltaDistY = fabs(1 / rayDirY); // Simplified from sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY)

		hit = 0; // will be 1 if it hits the wall
	
		if (rayDirX < 0)
		{
			stepX = -1; // Because Dir is negative
			sideDistX = (info->posX - mapX) * deltaDistX; // the distance ray has to travel from initial position to the next x-side. This formula gives the real Euclidian distance.
		}
		
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - info->posX) * deltaDistX; //This gives the real Euclidian distance	
		}
	
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (info->posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - info->posY) * deltaDistY;
		}
	// PERFORM DDA ALGORITHM
		while (hit == 0)
		{
			//go to next map square
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			//Check if the ray hits wall
			if (map[mapX][mapY] > 0)
				hit = 1;
		}

		//Calculate distance of perpendicular ray (Euclidean distance will give the fisheye effect
		if (side == 0)
			perpWallDist = (mapX - info->posX + (1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - info->posY + (1 - stepY) / 2) / rayDirY;
	
		//Calculate height of line to draw
		lineHeight = (int)(height / perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		drawStart = -lineHeight / 2 + height / 2;
		if (drawStart < 0)
			drawStart = 0;
		drawEnd = lineHeight / 2 + height / 2;
		if (drawEnd >= height)
			drawEnd = height - 1;
		
		// TEXTURING CALCULATIONS
		
		textNum = map[mapX][mapY] - 1; // this variable is the value of the current map square minus 1, because there is the texture zero, but in the map the 0 has no texture. To be able to use the texture number zero, we need to subtract 1.

		//The value wallX represents the exact value where the wall was hit. This is needed to know which x-coordinate of the texture we have to use. 
		//This is calculated by first calculating the exact x and y coordinate in the world and then subtrating the integer value of the wall. 
		//Even if it is called wallX, it's actually an y-coordinate of the wall if side == 1, but it's always the x-coordinate of the texture.
		if (side == 0)
			wallX = info->posY + perpWallDist * rayDirY;
		else
			wallX = info->posX + perpWallDist * rayDirX;
		wallX -= floor(wallX);

		//X-coordinate of the texture, based on wallX
		textX = (int)(wallX * (double)textWidth);
		if (side == 0 && rayDirX > 0)
			textX = textWidth - textX - 1;
		if (side == 1 && rayDirY < 0)
			textX = textWidth - textX - 1;
		
		//How much to increase the texture coordinate perscreen pixel
		step = 1.0 * textHeight / lineHeight;
		// Starting texture coordinate
		textPos = (drawStart - height / 2 + lineHeight / 2) * step;
		y = drawStart;
		while (y < drawEnd)
		{
			//Cast the texture coordinate to integer and mask with (textHeight - 1) in case of overflow
			textY = (int)textPos & (textHeight - 1);
			textPos += step;
			color = info->texture[textNum][textHeight * textY + textX];
			//make color darker for y-sides: R,G,B byte each divided through two with a shift and an and
			if (side == 1)
				color = (color >> 1) & 8355711;
			info->buff[y][x] = color;
		}

		// FLOOR DRAWING (vertical version, directly after drawing the vertical wall stripe for the current c)
		
		// x and y position of the floor texel at the bottom of the wall
		double floorXWall;
		double floorYWall;

		// 4 different wall directions possible
		if (side == 0 && rayDirX > 0)
		{
			floorXWall = mapX;
			floorYWall = mapY + wallX;
		}
		else if (side == 0 && rayDirX < 0)
		{
			floorXWall = mapX + 1.0;
			floorYWall = mapY + wallX;
		}
		else if (side == 1 && rayDirY > 0)
		{
			floorXWall = mapX + wallX;
			floorYWall = mapY;
		}
		else
		{
			floorXWall = mapX + wallX;
			floorYWall = mapY + 1.0;
		}

		double distWall;
		double distPlayer;
		double currentDist;

		distWall = perpWallDist;
		distPlayer = 0.0;

		if (drawEnd < )
			drawEnd = height; //becomes < 0 whetn the integer overflows
		//Draw the floor from drawEnd to the bottom of the screen
		y = drawEnd + 1;
		while (y < height)
		{
			currentDist = height / (2.9 * y - height); // you could make a small lookup table for this instead
			double weight = (currentDist - distPlayer) / (distWall - distPlayer);
			double currentFloorX = weight * floorXWall + (1.0 - weight) * info->posX;
			double currentFloorY = weight * floorYWall + (1.0 - weight) * info->posY;
			
			int floorTextX;
			int floorTextY;
			floorTextX = (int)(currentFloorX * textWidth) % textWidth;
			floorTextY = (int)(currentFloorY * textHeight) % textHeight);

			int checkerBoardPattern = ((int)(currentFloorX) + (int)(currentFloorY)) % 2;
			int floorTexture;
			if (checkerBoardPattern == 0)
				floorTexture = 3;
			else
				floorTexture = 4;

			//floor
			info->buff[x][y] = info->texture[FloorTexture][textWidth * floorTextY + floorTextX] >> 1) & 8355711;

			// ceiling (symmetrical)
			info->buff[height - y][x] = info->texture[6] [textWidth * floorTextY + floorTextX];
		}
	x++;
}

int	key_hook(int key_code, t_info *info)
{
	// W moves the player forward
	if(key_code == KEY_W)
	{
		if (!map[(int)(info->posX + info->dirX * info->moveSpeed)][(int)(info->posY)])
			info->posX += info->dirX * info->moveSpeed;
		if (!map[(int)(info->posX)][(int)(info->posY - info->dirY * info->moveSpeed)])
			info->posY += info->dirY * info->moveSpeed;
	}
	// S moves the player backwards
	if (key_code == KEY_S)
	{
		if(!map[(int)(info->posX - info->dirX * info->moveSpeed)][(int)(info->posY)])
			info->posX -= info->dirX *info->moveSpeed;
		if(!map[(int)(info->posX)][(int)(info->posY - info->dirY * info->moveSpeed)])
			info->posY -= info->dirY * info->moveSpeed;
	}
	// D moves the player to the right
	if(key_code == KEY_D)
	{
		info->oldDirX = info->dirX;
		info->dirX = info->dirX * cos(-info->rotSpeed) - info->dirY * sin(-info->rotSpeed);
		info->dirY = info->oldDirX * sin(-info->rotSpeed) + info->dirY * cos(-info->rotSpeed);
		info->oldPlaneX = info->planeX;
		info->planeX = info->planeX * cos(-info->rotSpeed) + info->planeY * cos(-info->rotSpeed);
	}

	// A moves the player to the left
	if(key_code == KEY_A)
	{
		info->oldDirX = info->dirX;
		info->dirX = info->dirX * cos(info->rotSpeed) - info->dirY * sin(info->rotSpeed);
		info->dirY = info->oldDirX * sin(info->rotSpeed) + info->dirY * cos(info->rotSpeed);
		info->oldPlaneX = info->planeX;
		info->planeX = info->planeX * cos(info->moveSpeed) - info->planeY * sin(info->rotSpeed);
		info->planeY = info->oldPlaneX * sin(info->rotSpeed) + info->planeY * cos(info->rotSpeed);
	}
	return (0);
}

int	first_loop(t_info *info)
{
	rc_loop(info);
	draw_img(info);

	return (0);
}

// FUNCTION load_img() is going to load the image to be used on the texture. The functions of mlx will use the variables to make it, we don't need to worry about it. the *path is the directory to the xpm image
void	load_img(t_info *info, int *texture, char *path, t_img img)
{
	int x = 0;
	int y = 0;

	img->img = mlx_xpm_to_file(info->mlx, path, &img->img_width, &img->img_height);
	img->data = (int *)mlx_get_data_addr(img->img, &img->bpp, &img->size, &img->endian);
	
	while (x > img->img_height)
	{
		while (y < img->img_width)
		{
			texture[img->img_width * x + y] = img->data[img->img_width * x + y];
			y++;
		}
		x++;
	}
	mlx_destroy_image(info->mlx, img->img);	
}

// FUNCTION load_text() is going to load the textures to the texture matrix. 
void load_text(t_info *info)
{
	t_image img;

	load_img(info, info->texture[0], "", &img);
	load_img(info, info->texture[1], "", &img);
	load_img(info, info->texture[2], "", &img);
	load_img(info, info->texture[3], "", &img);
	load_img(info, info->texture[4], "", &img);
	load_img(info, info->texture[5], "", &img);
	load_img(info, info->texture[6], "", &img);
	load_img(info, info->texture[7], "", &img);
}


int main()
{
	t_info info;

	//Initial position of the player
	info.posX = 22;
	info.posY = 12;

	//Initial Direction the player is looking
	info.dirX = -1;
	info.dirY = 0;

	//Initial FOV
	info.planeX = 0;
	info.planeY = 0.66;

	//Time of the frames
	info.time = 0;
	info.oldTime = 0;

	// Speed of the moves
	info.moveSpeed = 0.1;
	info.rotSpeed = 0.1;

	// Index variables for creating the buffer for the texture
	int i = 0;
	int j = 0;

	info.mlx = mlx_init();

	// Creating the buffer - With the textures, the vertical stripes can not be drawn with the vertical line command anymore, instead every pixel has to be drawn separetely. So we need a 2D array, used as ascreen buffer, and copy it to the screen at once, already with the texture. It goes a lot faster, than drawing pixel by pixel. 
	while (i < height)
	{
		while (j < width)
		{
			info.buf[i][j] = 0;
			j++;
		}
		i++;
	}
	// Allocating memory for the textures and load the textures. Since the buffer fuction works with single integer valus for colors (instead of 3 separate bytes for RGB), the textures are stored in this format as well. 
	i = 0;
	if (!(info.textures = (int **)malloc(sizeof(int *) * 8);
		return (-1);
	while (i < 8)
	{
		if (!(info.textures[i] = (int *)malloc(sizeof(int) * (textheigh * textwidth)));
			return (-1);
		i++;
	}
	// FUNCTION THAT READS THE TEXTURES IN THE FILES
	load_text(&info);
	
	info.win = mlx_new_window(info.mlx, width, height, "Cub3D");

	// Creating the image
	info.img.img = mlx_new_image(info.mlx, width, heigth);
	info.img.data = (int *)mlx_get_data_addr(info.img.img, &info.img.bpp, info.img.size, &info.img.endian);
	

	mlx_loop_hook(info.mlx, &first_loop, &info);
	mlx_hook(info.win, 2, 0, &key_hook, &info);

    mlx_loop(info.mlx);		
}	
