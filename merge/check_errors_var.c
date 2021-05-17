#include "cub3d.h"

int     check_resolution(char *line)
{
    int i;
    int set_of_n;

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
    {
        if (line[i] == ' ')
        {
            while (line[i] == ' ')
                i++;
        }
        if (ft_isdigit(line[i]) == 1)
        {
            set_of_n++;
            while (ft_isdigit(line[i]) == 1)
                i++;
        }
    }
    if (set_of_n != 2)
        return (-1);
    return 0;
}

int     check_c_f(char *line)
{
    int i;
    int set_of_n;

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
    {
        if (line[i] == ' ' || line[i] == ',')
        {
            while (line[i] == ' ' || line[i] == ',')
                i++;
        }
        if (ft_isdigit(line[i]) == 1)
        {
            set_of_n++;
            while (ft_isdigit(line[i]) == 1)
                i++;
        }
    }
    if (set_of_n != 3)
        return (-1);
    return 0;
}