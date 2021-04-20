#include "mlx.h"

#define mapWidth 24
#define mapHeight 24

typedef struct s_info
{
	void *mlx;
	void *win;
	double posX;
	double posY;
	double dirX;
	double dirY;
	double planeX;
	double planeY;
	double time;
	double oldtime;
	double moveSpeed;
	double rotSpeed;
	double oldDirX;
	double oldPlaneX;
}		t_info;

int map[mapwidth][mapHeight]=
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

// FUNTION DRAW_LINE - Draws the vertical lines in the window after calculation

void	draw_line(t_info *info, int x, int start, int end, int color)
{
	while(start <= end)
	{
		mlx_pixel_put(info->mlx, info->win, x, y, color);
		start++;
	}
}

// FUCTION RC_LOOP - It's the main loop where the raycasting and DDA algorithm happens. It will calculate where to put pixels and ask the draw_line() to draw it in the window

int	rc_loop(t_info *info)
{
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

	x = 0;
	while (x < 640) // 640 is width of window
	{
		cameraX = 2 * x / (double)width - 1; // 0 = middle, 1 = right, -1 = left
		rayDirX = info->dirX + info->planeX * cameraX; 
		rayDirY = info->dirY + indo->planeY * cameraX; // Sum of the direction of the player and a part of the plane
		mapX = (int)info->posX; 
		mapY = (int)info->posY; //the ray starts in the same position as the player
		deltaDistX = abs(1 / rayDirX); //Simplified from sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX)
		deltaDistY = abs(1 / rayDirY); // Simplified from sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY)

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
			//Check if it is wall
			if (worldMap[mapX][mapY] > 0)
				hit = 1;
		}
		if (side == 0)
			perpWallDist = (mapX - info->posX + (1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - info->posY + (1 - stepY) / 2) / rayDirY;
	
		//Calculate height of line to draw
		lineHeight = (int)(height / perpWallDist);
		drawStart = -lineHeight / 2 + height / 2;
		if (drawStart < 0)
			drawStart = 0;
		drawEnd = lineHeight / 2 + height / 2;
		if (drawEnd >= height)
			drawEnd = height - 1;
	
		if (worldMap[mapX][mapY] == 1)
			color = 0xFF0000;
		else
			color = 0xFFFF00;
	
		draw_line(info, x, drawStart, drawEnd, color);
		x++;
		}
	}
	return (0);
}

int	key_hook(int key_code, t_info *info)
{
	// W moves the player forward
	if(key_code == KEY_W)
	{
		if (!WorldMap[(int)(info->posX + info->dirX * info->moveSpeed)][(int)(info->posY)]
			info->posX += info->dirX * info->moveSpeed;
		if (!worldMap[(int)(info->posX)][(int)info->posY - info->dirY * info->moveSpeed)])
			info->posY += info->dirY * info->moveSpeed;

	// S moves the player backwards
	if (key_code == KEY_S)
	{
		if(!worldMap[(int)(info->posX - info->dirX * info->moveSpeed)][(int)(info->posY)])
			info->posX -= dirX *info->moveSpeed;
		if(!worldMap[(int)(info->posX)][(int)(info->posY - info->dirY * info->moveSpeed)])
			info-posY -= dirY * info->moveSpeed;
	
	// D moves the player to the right
	if(key_code == K_D)
	{
		info->oldDirX = info->dirX;
		info->dirX = info->dirX * cos(-info->rotSpeed) - info->dirY * sin(-info->rotSpeed);
		info->dirY = info->oldDirX * sin(-info->rotSpeed) + info->dirY * cos(-info->rotSpeed);
		oldPlaneX = planeX;
		planeX = planeX * cos(-info->rotSpeed) + planeY * cos(-info->rotSpeed);
	}

	// A moves the player to the left
	if(key_code == K_A)
	{
		info->oldDirX = info->dirX;
		info->dirX = info->dirX * cos(info->rotSpeed) - info->dirY * sin(info->rotSpeed);
		info->dirY = oldDirX * sin(info->rotSpeed) + info->dirY * cos(info->rotSpeed);
		info->oldPlaneX = info->planeX;
		info->planeX = info->planeX * cos(info->moveSpeed) - info->planeY * sin(info->rotSpeed);
		info->planeY = info->oldPlaneX * sin(info->rotSpeed) + planeY * cos(info->rotSpeed);
	}
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
	info.moveSpeed = 0.05;
	info.rotSpeed = 0.05;

	info.mlx = mlx_init();
	info.win = mlx_new_window(info.mlx, 640, 480, "Cub3D");

	mlx_loop_hook(info.mlx, &rc_loop, &info);
	mlx_hook(info.win, 2, 0, &key_hook, &info);

       	mlx_loop(info.mlx);	
}
