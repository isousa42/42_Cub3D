#include "gnl.h"

int     check_sides_one(char **save, int size)
{
    int x;
    int y;
    int z;

    x = 0;
    z = 0;
    while (x < size)
    {
        y = 0;
        while (y < ft_strlen(save[x]))
        {
            if (x == 0 || y == 0)
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
            if ((x == size - 1) || (y == ft_strlen(save[x]) - 1))
            {
                if ((ft_iswall(save[x][y]) == 0))
                    return (-1);
                if (save[x][y] == ' ')
                {
                    z = ft_strlen(save[x]);
                    while (save[x][z] == ' ')
                        z--;
                    if (save[x][z] != '1')
                        return (-1);
                }
            }
            y++;
        }
        x++;
    }
    return (0);
}

int     check_inside(char **save, int size)
{
    int x;
    int y;

    x = 1;
    while (x < size)
    {
        y = 1;
        while (y < ft_strlen(save[x]))
        {
            while (save[x][y] == ' ')
                y++;
            if (save[x][y] != '0' && save[x][y] != '1' && save[x][y] != '2' && save[x][y] != 'N' && save[x][y] != 'S' && save[x][y] != 'W' && save[x][y] != 'E')
                return (-1);
            y++;
        }
        x++;
    }
    return (0);
}

int     check_letters(char **save, int size)
{
    int x;
    int y;
    int counter;

    x = 1;
    counter = 0;
    while (x < size)
    {
        y = 1;
        while (y < ft_strlen(save[x]))
        {
            while (save[x][y] == ' ')
                y++;
            if (save[x][y] == 'N' || save[x][y] == 'S' || save[x][y] == 'W' || save[x][y] == 'E')
                counter++;
            y++;
        }
        x++;
    }
    return (counter);
}

int     check_close(char **save, int size)
{
    int x;
    int y;

    x = 1;
    while (x < size)
    {
        y = 1;
        while (y < ft_strlen(save[x]))
        {
            while(save[x][y] == ' ')
                y++;
            if (save[x][y] == '0' && (save[x + 1][y] != '1' && save[x + 1][y] != '0' && save[x + 1][y] != '2'))
                return (-1);
            if (save[x][y] == '0' && (save[x - 1][y] != '1' && save[x - 1][y] != '0' && save[x - 1][y] != '2'))
                return (-1);
            y++;
        }
        x++;
    }
    return (0);
}