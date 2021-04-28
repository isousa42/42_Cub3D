#include "mlx.h"
#include <unistd.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define mapWidth 24
#define mapHeight 24
#define width 640
#define height 480
#define textWidth 64
#define textHeight 64

#define X_EVENT_KEY_PRESS	2
#define X_EVENT_KEY_EXIT	17

#define KEY_W 13
#define KEY_S 1
#define KEY_A 0
#define KEY_D 2
#define KEY_ESC 53

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

typedef struct s_info
{
	void *mlx;
	void *win;
	t_image img;
	int	buff[height][width];
	int	**texture;
	double posX;
	double posY;
	double dirX;
	double dirY;
	double planeX;
	double planeY;
	double moveSpeed;
	double rotSpeed;
}		t_info;

int	ft_handle_text(t_info *info);
void	load_text(t_info *info);
void	load_img(t_info *info, int *texture, char *path, t_image *img);

void    ft_init_info(t_info *info);