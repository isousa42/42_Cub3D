#include "cub3d.h"

void	read_file(t_info *info)
{
	int		fd;
	int		ret;
	char	*line;
	t_list	*lista;

	lista = NULL;
	info->save = NULL;
	ret = 1;
	line = NULL;
	fd = open(info->file_path, O_RDONLY);
	if (fd == -1)
	{
		printf("ERROR = NOT ABLE TO READ THE FILE");
		exit(0);
	}
	while (ret > 0)
	{
		ret = get_next_line(fd, &line);
		parse_file(info, &lista, line);
	}
	close(fd);
	check_width(info);
	init_map(info, lista);
	check_errors_map(info->map, info->size_list);
	init_pos(info);
}

void	parse_file(t_info *info, t_list **lista, char *line)
{
	if (line[0] == 'R')
		parse_r(info, line);
	else if (line[0] == 'F')
		parse_f(info, line);
	else if (line[0] == 'C')
		parse_c(info, line);
	else if (line[0] == 'N' && line[1] == 'O')
		parse_variable(info, line, 1);
	else if (line[0] == 'S' && line[1] == 'O')
		parse_variable(info, line, 2);
	else if (line[0] == 'W' && line[1] == 'E')
		parse_variable(info, line, 3);
	else if (line[0] == 'E' && line[1] == 'A')
		parse_variable(info, line, 4);
	else if (line[0] == 'S' && line[1] == ' ')
		parse_variable(info, line, 5);
	else
		ft_lstadd_back(lista, ft_lstnew((void *)line));
}

void	check_width(t_info *info)
{
	if (info->width == 1920)
		info->width = 1921;
	if (info->width >= 2560)
		info->width = 2559;
	if (info->height >= 1440)
		info->height = 1439;
	if (info->width <= 9)
		info->width = 10;
	if (info->height <= 9)
		info->height = 10;
}

void	init_map(t_info *info, t_list *lista)
{
	int	x;

	x = 0;
	info->size_list = ft_lstsize(lista);
	info->map = ft_calloc(info->size_list, sizeof(char *));
	while (lista)
	{
		info->map[x] = ft_strdup(lista->content);
		lista = lista->next;
		x++;
	}
}

void	init_pos(t_info *info)
{
	int	x;
	int	y;

	x = 0;
	while (x < info->size_list)
	{
		y = 0;
		while (y < ft_strlen(info->map[x]))
		{
			if (ft_isalpha(info->map[x][y]) == 1)
			{
				info->posX = x + 0.5;
				info->posY = y + 0.5;
				info->direction = info->map[x][y];
				info->map[x][y] = '0';
			}
			y++;
		}
		x++;
	}
}
