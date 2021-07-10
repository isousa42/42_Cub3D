#include "cub3d.h"

void	help_check_res(char *line, int *i, int *set_of_n)
{
	if (line[*i] == ' ')
	{
		while (line[*i] == ' ')
			(*i)++;
	}
	if (ft_isdigit(line[*i]) == 1)
	{
		(*set_of_n)++;
		while (ft_isdigit(line[*i]) == 1)
			(*i)++;
	}
}

int	check_resolution(char *line)
{
	int	i;
	int	set_of_n;

	i = 1;
	set_of_n = 0;
	while (line[i])
	{
		if (ft_isdigit(line[i]) == 0 && line[i] != ' ')
			return (-1);
		i++;
	}
	i = 1;
	while (line[i])
		help_check_res(line, &i, &set_of_n);
	if (set_of_n != 2)
		return (-1);
	return (0);
}

void	help_check_cf(char *line, int *i, int *set_of_n)
{
	if (line[*i] == ' ' || line[*i] == ',')
	{
		while (line[*i] == ' ' || line[*i] == ',')
			(*i)++;
	}
	if (ft_isdigit(line[*i]) == 1)
	{
		(*set_of_n)++;
		while (ft_isdigit(line[*i]) == 1)
			(*i)++;
	}
}

int	check_c_f(char *line)
{
	int	i;
	int	set_of_n;

	i = 1;
	set_of_n = 0;
	while (line[i])
	{
		if (ft_isdigit(line[i]) == 0 && line[i] != ' ' && line[i] != ',')
			return (-1);
		i++;
	}
	i = 1;
	while (line[i])
		help_check_cf(line, &i, &set_of_n);
	if (set_of_n != 3)
		return (-1);
	return (0);
}
