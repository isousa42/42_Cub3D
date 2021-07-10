#include "cub3d.h"

int	check_arg(char *arg)
{
	if (arg[0] != '-')
		return (-1);
	if (arg[1] != '-')
		return (-1);
	if (arg[2] != 's')
		return (-1);
	if (arg[3] != 'a')
		return (-1);
	if (arg[4] != 'v')
		return (-1);
	if (arg[5] != 'e')
		return (-1);
	return (0);
}

void	check_args(int argc, char **argv, t_info *info)
{
	if (argc == 1)
	{
		printf("ERROR = YOU FORGOT TO PUT THE FILE (.cub)");
		exit(0);
	}
	else if (argc == 2 || argc == 3)
		info->file_path = ft_strdup(argv[1]);
	if (argc == 3)
	{
		if ((check_arg(argv[2])) == 0)
			info->take_pic = 1;
		else
		{
			printf("ERROR = IF YOU WANT A SCREENSHOT SPELL IT RIGTH!");
			exit(0);
		}
	}
}
