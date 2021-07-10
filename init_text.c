#include "cub3d.h"

int	load_img(t_info *info, int *texture, char *path, t_image *img)
{
	int	x;
	int	y;

	img->img = mlx_xpm_file_to_image(info->mlx, path, &img->img_width,
			&img->img_height);
	if (!img->img)
		return (-1);
	img->data = (int *)mlx_get_data_addr(img->img, &img->bpp, &img->size,
			&img->endian);
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
	return (0);
}

void	free_text(t_info *info, int control)
{
	if (control == 1)
		printf("ERROR = NOT POSSIBLE TO UPLOAD THE TEXTURE (NO)!");
	else if (control == 2)
		printf("ERROR = NOT POSSIBLE TO UPLOAD THE TEXTURE (SO)!");
	else if (control == 3)
		printf("ERROR = NOT POSSIBLE TO UPLOAD THE TEXTURE (WE)!");
	else if (control == 4)
		printf("ERROR = NOT POSSIBLE TO UPLOAD THE TEXTURE (EA)!");
	else if (control == 5)
		printf("ERROR = NOT POSSIBLE TO UPLOAD THE TEXTURE (S)!");
	free(info->texture);
	free(info->buff);
	free(info->sprites.sprites_buff);
	exit(0);
}

void	load_text(t_info *info)
{
	t_image	img;

	if (load_img(info, info->texture[0], info->flagNO, &img) == -1)
		free_text(info, 1);
	if (load_img(info, info->texture[1], info->flagSO, &img) == -1)
		free_text(info, 2);
	if (load_img(info, info->texture[2], info->flagWE, &img) == -1)
		free_text(info, 3);
	if (load_img(info, info->texture[3], info->flagEA, &img) == -1)
		free_text(info, 4);
	if (load_img(info, info->texture[4], info->flagS, &img) == -1)
		free_text(info, 5);
}

int	handle_buff(t_info *info)
{
	int	i;

	i = -1;
	info->buff = ft_calloc(info->height, sizeof(int **));
	while (++i < info->height)
		info->buff[i] = ft_calloc(info->width, sizeof(int *));
	info->texture = ft_calloc(5, sizeof(int **));
	i = -1;
	while (++i < 5)
		info->texture[i] = ft_calloc(TEXTHEIGHT * TEXTWIDTH, sizeof(int *));
	load_text(info);
	return (0);
}
