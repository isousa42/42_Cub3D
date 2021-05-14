#include "cub3d.h"

void	load_img(t_info *info, int *texture, char *path, t_image *img)
{
	int x;
	int y;

	img->img = mlx_xpm_file_to_image(info->mlx, path, &img->img_width, &img->img_height);
	img->data = (int *)mlx_get_data_addr(img->img, &img->bpp, &img->size, &img->endian);
	y = 0;
	while (y < img->img_height)
	{
		x = 0;
		while (x < img->img_width)
		{
			texture[img->img_width * y + x] = img->data[img->img_width * y + x];
			x++;
		}
		y++;
	}
	mlx_destroy_image(info->mlx, img->img);	
}

void	load_text(t_info *info)
{
	t_image	img;

	load_img(info, info->texture[0], "textures/eagle.xpm", &img);
	load_img(info, info->texture[1], "textures/redbrick.xpm", &img);
	load_img(info, info->texture[2], "textures/purplestone.xpm", &img);
	load_img(info, info->texture[3], "textures/greystone.xpm", &img);
	load_img(info, info->texture[4], "textures/bluestone.xpm", &img);
	load_img(info, info->texture[5], "textures/mossy.xpm", &img);
	load_img(info, info->texture[6], "textures/wood.xpm", &img);
	load_img(info, info->texture[7], "textures/colorstone.xpm", &img);
}

int	ft_handle_text(t_info *info)
{
	int i;
	int j;

	i = 0;
	j = 0;
	// Creating the buffer - With the textures, the vertical stripes can not be drawn with the vertical line command anymore, 
	//instead every pixel has to be drawn separetely. So we need a 2D array, used as ascreen buffer, 
	// and copy it to the screen at once, already with the texture. It goes a lot faster, than drawing pixel by pixel. 
	if (!(info->buff = (int **)malloc(sizeof(int **) * info->height)))
		return (1);
	while (i < info->height)
	{
		//printf("ADDING A ROW %i\n", i);
		if(!(info->buff[i] = (int *)malloc(sizeof(int *) * info->width)))
			return (1);
		i++;
	}
	
	i = 0;
	while (i < info->height)
	{
		j = 0;
		while (j < info->width)
		{
			info->buff[i][j] = 0;
			//printf("%d - %d\n", info->buff[i][j], i);
			j++;
		}
		i++;
	}
	// Allocating memory for the textures and load the textures. Since the buffer fuction works 
	//with single integer valus for colors (instead of 3 separate bytes for RGB), the textures are stored 
	//in this format as well. 
	i = 0;
	if (!(info->texture = (int **)malloc(sizeof(int **) * 8)))
		return (1);
	while (i < 8)
	{
		if (!(info->texture[i] = (int *)malloc(sizeof(int *) * (textHeight * textWidth))))
			return (1);
		i++;
	}
	i = 0;
	j = 0;
	while (i < 8)
	{
		j = 0;
		while (j < textHeight * textWidth)
		{
			info->texture[i][j] = 0;
			j++;
		}
		i++;
	}
	// FUNCTION THAT READS THE TEXTURES IN THE FILES
	load_text(info);
	return (0);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t i;

	i = 0;
	if (!dest && !src)
		return (0);
	while (i < n)
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dest);
}

void init_map(t_info *info)
{
	int world_map[mapWidth][mapHeight]=
	{
		{5,5,5,2,2,5,5,5},
		{5,0,0,0,0,0,0,5},
		{5,0,0,0,0,0,0,5},
		{5,0,0,0,0,0,0,5},
		{5,0,0,0,0,0,0,5},
		{5,0,0,0,0,0,0,5},
		{5,0,0,0,0,0,0,5},
		{5,5,5,5,5,5,5,5},
		
	};
	ft_memcpy(info->map, world_map, sizeof(int) * (mapHeight * mapWidth));
}