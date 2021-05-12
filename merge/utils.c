#include "cub3d.h"

void	draw_img(t_info *info)
{
	for (int y = 0; y < info->height; y++)
	{
		for (int x = 0; x < info->width; x++)
		{
			info->img.data[y * info->width + x] = info->buff[y][x];
		}
	}
	mlx_put_image_to_window(info->mlx, info->win, info->img.img, 0, 0);
	
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, count * size);
	return (ptr);
}

void	ft_bzero(void *str, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)str)[i] = '\0';
		i++;
	}
}