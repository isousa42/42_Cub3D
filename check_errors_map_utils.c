#include "cub3d.h"

int	start_map(char **save)
{
	int	counter;
	int	x;

	counter = 0;
	x = 0;
	while (!save[x][0])
	{
		counter++;
		x++;
	}
	return (counter);
}

int	counter_map(char **save, int first, int size)
{
	int	counter;
	int	x;

	counter = 0;
	x = first + 1;
	while (x < size)
	{
		if (!save[x][0])
			counter = counter + 1;
		x++;
	}
	return (counter);
}

int	help_checker(char **save, int x, int y, int first)
{
	int	z;

	if (x == first || y == 0)
	{
		if (ft_iswall(save[x][y]) == 0)
			return (-1);
		if (save[x][y] == ' ')
		{
			z = 0;
			while (save[x][z] == ' ')
				z++;
			if (save[x][z] != '1')
				return (-1);
		}
	}
	return (0);
}

int	check_what_it_is(char **save, int x, int y, int control)
{
	if (control == 1)
	{
		if ((save[x][y] == '0' || save[x][y] == '2')
			&& (save[x + 1][y] != '1' && save[x + 1][y] != '0'
			&& save[x + 1][y] != '2' && save[x + 1][y] != 'W'
			&& save[x + 1][y] != 'N' && save[x + 1][y] != 'S'
			&& save[x + 1][y] != 'E' && !save[x + 1]))
			return (-1);
	}
	else if (control == 2)
	{
		if ((save[x][y] == '0' || save[x][y] == '2')
			&& (save[x - 1][y] != '1' && save[x - 1][y] != '0'
			&& save[x - 1][y] != '2' && save[x - 1][y] != 'W'
			&& save[x - 1][y] != 'N' && save[x - 1][y] != 'S'
			&& save[x - 1][y] != 'E' && !save[x - 1]))
			return (-1);
	}
	return (0);
}

int	check_other_things(char **save, int x, int y)
{
	if (save[x][y] == ' ' && save[x + 1][y] != '1')
		return (-1);
	if (save[x][y] == ' ' && save[x - 1][y] != '1')
		return (-1);
	if (save[x][y] == ' ' && save[x][y + 1] != '1')
		return (-1);
	if (save[x][y] == ' ' && save[x][y - 1] != '1')
		return (-1);
	if ((save[x][y] == '0' || save[x][y] == '2') && save[x + 1][y] == ' ')
		return (-1);
	if ((save[x][y] == '0' || save[x][y] == '2') && save[x - 1][y] == ' ')
		return (-1);
	if ((save[x][y] == '0' || save[x][y] == '2') && !save[x + 1][y])
		return (-1);
	if ((save[x][y] == '0' || save[x][y] == '2') && !save[x - 1][y])
		return (-1);
	return (0);
}
