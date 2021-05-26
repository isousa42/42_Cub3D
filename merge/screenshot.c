#include "cub3d.h"

void	conv_int(unsigned char *start, int value)
{
	start[0] = (unsigned char)(value);
	start[1] = (unsigned char)(value >> 8);
	start[2] = (unsigned char)(value >> 16);
	start[3] = (unsigned char)(value >> 24);
}

int	write_header(int fd, int filesize, t_info *info)
{
	int				i;
	int				tmp;
	unsigned char	bmpfileheader[54];

	i = 0;
	while (i < 54)
		bmpfileheader[i++] = (unsigned char)(0);
	bmpfileheader[0] = (unsigned char)('B');
	bmpfileheader[1] = (unsigned char)('M');
	conv_int(bmpfileheader + 2, filesize);
	bmpfileheader[10] = (unsigned char)(54);
	bmpfileheader[14] = (unsigned char)(40);
	tmp = info->width;
	conv_int(bmpfileheader + 18, tmp);
	tmp = info->height;
	conv_int(bmpfileheader + 22, tmp);
	bmpfileheader[27] = (unsigned char)(1);
	bmpfileheader[28] = (unsigned char)(24);
	return (!(write(fd, bmpfileheader, 54) < 0));
}

void	write_image(int file, t_info *info)
{
	int					i;
	int					j;

	i = info->height - 1;
	while (i >= 0)
	{
		j = 0;
		while (j < info->width)
		{
			write(file, &info->buff[i][j], 3);
			j++;
		}
		i--;
	}
}

void	take_screenshot(t_info *info)
{
	int	fd;
	int	fz;
	int	i;

	if (info->width > 1500)
		info->width = 1500;
	rc_loop(info);
	fz = 54 + (3 * (info->height * info->width));
	fd = open("screenshot.bmp", O_WRONLY | O_CREAT, 0777 | O_TRUNC | O_APPEND);
	write_header(fd, fz, info);
	write_image(fd, info);
	close(fd);
}
