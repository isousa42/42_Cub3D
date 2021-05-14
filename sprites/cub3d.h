#include "mlx.h"
#include <unistd.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define mapWidth 8
#define mapHeight 8
#define textWidth 64
#define textHeight 64

#define X_EVENT_KEY_PRESS	2
#define X_EVENT_KEY_EXIT	17

#define KEY_W 13
#define KEY_S 1
#define KEY_A 0
#define KEY_D 2
#define KEY_ESC 53

typedef struct s_rc
{
	int j;
	int y;
	float rayDirX0;
	float rayDirY0;
	float rayDirY1;
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
	int color;
	int x;
	double cameraX;
	double rayDirX; 
	double rayDirY; 
	int mapX; 
	int mapY; 
	double sideDistX;
	double sideDistY;
	double deltaDistX; 
	double deltaDistY; 
	double perpWallDist;
	int stepX;
	int stepY;
	int hit; 
	int side; 
	int lineHeight;
	int drawStart;
	int drawEnd;
	int textNum;
	double wallX;
	int textX;
	double step;
	double textPos;
	int i;
	int textY;
	double distWall;
	double distPlayer;
	double currentDist;
	double weight;
	double currentFloorX;
	double currentFloorY;
	int floorTextX;
	int floorTextY;
	int checkerBoardPattern;
	int floorTexture;
	double floorXWall;
	double floorYWall;
}		t_rc;

typedef struct s_keys
{
	int key_w;
	int key_s;
	int key_a;
	int key_d;
	int key_esc;
}		t_keys;

typedef struct s_image
{
	void	*img;
	int	*data;
	int	size;
	int	bpp;
	int	endian;
	int	img_width;
	int	img_height;
}		t_image;

typedef struct s_sprites
{
	double *sprites_buff;
	double inversion;
	double depthX;
	double depthY;
	double screenX;
	int spriteHeight;
	int drawStartY;
	int drawEndY;
	int spriteWidth;
	int drawStartX;
	int drawEndX;
	int sprite;
	int textX;
	int avoid_overflow;
	int sprite_color;
	int textY;
	int move;

}		t_sprites;

typedef struct s_info
{
	void *mlx;
	void *win;
	t_image img;
	t_keys keys;
	t_rc rc;
	t_sprites sprites;
	int map[mapWidth][mapHeight];
	int	**buff;
	int	**texture;
	double posX;
	double posY;
	double dirX;
	double dirY;
	double planeX;
	double planeY;
	double moveSpeed;
	double rotSpeed;
	//ceiling rgb
	int rgb_ceiling;
	//floor rgb
	int rgb_floor;
	//sprites
	

	
	int width;
	int height;
}		t_info;

// cub3d.c
void	rc_loop(t_info *info);
int		first_loop(t_info *info);


// init_test.c
int		ft_handle_text(t_info *info);
void	load_text(t_info *info);
void	load_img(t_info *info, int *texture, char *path, t_image *img);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	init_map(t_info *info);

// init_info.c
void    ft_init_info(t_info *info);
void	init_play_pos(t_info *info);

// keys.c
int		key_release(int keycode, t_info *info);
int		key_press(int keycode, t_info *info);
int		key_hook(t_info *info);
void	init_key(t_info *info);

// floor.c
void    floor_draw(t_info *info);
void	floor_init(t_info *info);
void	floor_calculations(t_info *info);
void	floor_setup(t_info *info);
int		create_rgb(int r, int g, int b);

// wall.c

void    wall_init(t_info *info);
void    ray_walking(t_info *info);
void    dda_algorithm(t_info *info);
void	wall_calc(t_info *info);
void	wall_text(t_info *info);

// sprites.c
void	sprites_draw(t_info *info, double spriteX, double spriteY, int texture);


//utils.c
void	draw_img(t_info *info);
void	*ft_calloc(size_t count, size_t size);
void	ft_bzero(void *str, size_t n);



