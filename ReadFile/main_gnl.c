#include "gnl.h"

void    parse_file(t_file *file, char **save)
{
    file->flagRY = 0;
    file->flagRY = 0;
    int y;
    int x;

    x = 0;
    y = 0;
    while(save[x] != 0)
    {
        if (save[x][y] == 'R')
            parse_r(file, save, x, y);
        else if (save[x][y] == 'N' && save[x][y + 1] == 'O')
            parse_no(file, save, x, y);
        else if (save[x][y] == 'S' && save[x][y + 1] == 'O')
            parse_so(file, save, x, y);
        else if (save[x][y] == 'W' && save[x][y + 1] == 'E')
            parse_we(file, save, x, y);
        else if (save[x][y] == 'E' && save[x][y + 1] == 'A')
            parse_ea(file, save, x, y);
        else if (save[x][y] == 'S' && save[x][y + 1] == ' ')
            parse_s(file, save, x, y);
        else if (save[x][y] == 'F')
            parse_f(file, save, x, y);
        else if (save[x][y] == 'C')
            parse_c(file, save, x, y);
        else
        {
            parse_map(file, save, x);
            break;
        }
        x++;
    }
}

int     check_error(char **save)
{
    int x;
    int y;
    
    x = 0;
    y = 0;
    while(1)
    {
        y = 0;
        if (save[x][y] == 'R')
        {
            y++;
            if(save[x][y] != ' ')
                return (-1);
            else
                y++;
            while (ft_isdigit(save[x][y]) == 1)
                y++;
            if(save[x][y] != ' ' && save[x][y] != ',')
                return (-1);
            else
                y++;
            while (ft_isdigit(save[x][y]) == 1)
                y++;
            if (save[x][y] != 0)
                return (-1);
        }
        else if (save[x][y] == 'N' && save[x][y + 1] == 'O')
        {
            y = y + 3;
            if(save[x][y] != '.' && save[x][y + 1] != '/')
                return (-1);
        }
        else if (save[x][y] == 'S' && save[x][y + 1] == 'O')
        {
            y = y + 3;
            if(save[x][y] != '.' && save[x][y + 1] != '/')
                return (-1);
        }
        else if (save[x][y] == 'W' && save[x][y + 1] == 'E')
        {
            y = y + 3;
            if(save[x][y] != '.' && save[x][y + 1] != '/')
                return (-1);
        }
        else if (save[x][y] == 'E' && save[x][y + 1] == 'A')
        {
            y = y + 3;
            if(save[x][y] != '.' && save[x][y + 1] != '/')
                return (-1);
        }
        else if (save[x][y] == 'S' && save[x][y + 1] == ' ')
        {
            y = y + 2;
            if(save[x][y] != '.' && save[x][y + 1] != '/')
                return (-1);
        }
        else if (save[x][y] == 'F')
        {
            y++;
            if(save[x][y] != ' ')
                return (-1);
            else
                y++;
            while (ft_isdigit(save[x][y]) == 1)
                y++;
            if(save[x][y] != ' ' && save[x][y] != ',')
                return (-1);
            else
                y++;
            while (ft_isdigit(save[x][y]) == 1)
                y++;
            if(save[x][y] != ' ' && save[x][y] != ',')
                return (-1);
            else
                y++;
            while (ft_isdigit(save[x][y]) == 1)
                y++;
            printf("%c", save[x][y]);
            if (save[x][y] != 0)
                return (-1);
        }
        else if (save[x][y] == 'C')
        {
            y++;
            if(save[x][y] != ' ')
                return (-1);
            else
                y++;
            while (ft_isdigit(save[x][y]) == 1)
                y++;
            if(save[x][y] != ' ' && save[x][y] != ',')
                return (-1);
            else
                y++;
            while (ft_isdigit(save[x][y]) == 1)
                y++;
            if(save[x][y] != ' ' && save[x][y] != ',')
                return (-1);
            else
                y++;
            while (ft_isdigit(save[x][y]) == 1)
                y++;
            printf("%c", save[x][y]);
            if (save[x][y] != 0)
                return (-1);
        }
        if (save[x][y] == '1')
            return (0);
        x++;

    }
    return (0);
}

int main()
{
    // SAVING ALL INFORMATION IN THE FILE IN THE MATRIX **save
    int fd;
    int ret;
    int x;
    char *line;
    char **save;
    t_file file;

    x = 0;
    ret = 0;
    line = NULL;

    fd = open("cub3d.cub", O_RDONLY);
    save = (char **)malloc(sizeof(char *) * (40));
	if (!save)
		return (0);
    while ((ret = get_next_line(fd, &line)) > 0)
    {
        save[x] = ft_strdup(line);
        x++;
        free(line);
    }
    save[x] = "\0";
    close(fd);

    if (check_error(save) == -1)
    {
        printf("error");
        return 0;
    }
    parse_file(&file, save);
    return 0;
}