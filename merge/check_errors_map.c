#include "cub3d.h"

void	check_errors_map(char **save, int size)
{
	if (check_close(save, size) == -1)
	{
		printf("ERROR = MAP IS NOT CLOSE! CHANGE IT SO PLAYER CAN NOT ESCAPE!");
		exit(0);
	}
	if (check_outside(save, size) == -1)
	{
		printf("ERROR = THERE IS A ERROR! CHANGE IT SO PLAYER CAN NOT ESCAPE!");
		exit(0);
	}
	if (check_inside(save, size) == -1)
	{
		printf("\033[1;32mERROR = SOMETHING WRONG IN MAP. CORRECT IT (please)");
		exit(0);
	}
	if (check_letters(save, size) != 1)
	{
		printf("ERROR = NO PLAYER OR MORE THAN ONE PLAYER. CHANGE IT.");
		exit(0);
	}
}

int	check_outside(char **save, int size)
{
	int	x;
	int	y;
	int	empty;
	int	first;

	x = 0;
	first = start_map(save);
	empty = counter_map(save, first, size) + 1;
	while (x < size)
	{
		y = 0;
		while (y < ft_strlen(save[x]))
		{
			if (help_checker(save, x, y, first) == -1)
				return (-1);
			if (x == size - empty || (y + 1 == ft_strlen(save[x])))
			{
				if ((ft_iswall(save[x][y]) == 0))
					return (-1);
			}
			y++;
		}
		x++;
	}
	return (0);
}

int	check_inside(char **save, int size)
{
	int	x;
	int	y;
	int	first;

	first = start_map(save);
	x = first + 1;
	while (x < (size - counter_map(save, first, size)))
	{
		y = 1;
		while (y < ft_strlen(save[x]))
		{
			while (save[x][y] == ' ')
				y++;
			if (save[x][y] != '0' && save[x][y] != '1' && save[x][y] != '2'
				&& save[x][y] != 'N' && save[x][y] != 'S'
				&& save[x][y] != 'W' && save[x][y] != 'E')
				return (-1);
			y++;
		}
		x++;
	}
	return (0);
}

int	check_letters(char **save, int size)
{
	int	x;
	int	y;
	int	counter;
	int	first;

	first = start_map(save);
	x = first + 1;
	counter = 0;
	while (x < (size - counter_map(save, first, size)))
	{
		y = 1;
		while (y < ft_strlen(save[x]))
		{
			while (save[x][y] == ' ')
				y++;
			if (save[x][y] == 'N' || save[x][y] == 'S'
				|| save[x][y] == 'W' || save[x][y] == 'E')
				counter++;
			y++;
		}
		x++;
	}
	return (counter);
}

int	check_close(char **save, int size)
{
	int	x;
	int	y;
	int	first;

	first = start_map(save);
	x = first + 1;
	while (x < (size - (counter_map(save, first, size) + 1)))
	{
		y = 1;
		while (y < ft_strlen(save[x]))
		{
			while (save[x][y] == ' ')
				y++;
			if (check_other_things(save, x, y) == -1)
				return (-1);
			if (check_what_it_is(save, x, y, 1) == -1)
				return (-1);
			if (check_what_it_is(save, x, y, 2) == -1)
				return (-1);
			y++;
		}
		x++;
	}
	return (0);
}
