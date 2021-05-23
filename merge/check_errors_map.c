#include "cub3d.h"

void    check_errors_map(char **save, int size)
{
    if(check_close(save, size) == -1)
    {
        printf("ERROR = MAP IS NOT CLOSE! CHANGE IT SO PLAYER CAN NOT ESCAPE!");
        exit(0);
    }
    if(check_outside(save, size) == -1)
    {
        printf("ERROR = THERE IS A ERROR OUTSIDE! CHANGE IT SO PLAYER CAN NOT ESCAPE!");
        exit(0);
    }
    if(check_inside(save, size) == -1)
    {
        printf("\033[1;32mERROR = SOMETHING WRONG INSIDE THE MAP. CORRECT IT (please.)");
        exit(0);
    }
    if (check_letters(save, size) != 1)
    {
        printf("ERROR = NO PLAYER OR MORE THAN ONE PLAYER. CHANGE IT.");
        exit(0);
    }
}

int     start_map(char **save)
{
    int counter;
    int x;

    counter = 0;
    x = 0;
    while (!save[x][0])
    {
        counter++;
        x++;
    }
    return (counter);
}

int     counter_map(char **save, int first, int size)
{
    int counter;
    int x;

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

int help_checker(char **save, int x, int y, int first)
{
    int z;
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

int     check_outside(char **save, int size)
{
    int x;
    int y;
    int z;
    int empty;
    int first;

    x = 0;
    z = 0;
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

int     check_inside(char **save, int size)
{
    int x;
    int y;
    int first;

    first = start_map(save);
    x = first + 1;
    while (x < (size - counter_map(save, first, size)))
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
    int first;

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
            if (save[x][y] == 'N' || save[x][y] == 'S' || save[x][y] == 'W' || save[x][y] == 'E')
                counter++;
            y++;
        }
        x++;
    }
    return (counter);
}

int     check_other_things(char **save, int x, int y)
{
    if (save[x][y] == ' ' && save[x + 1][y] !=  '1')
        return(-1);
    if (save[x][y] == ' ' && save[x - 1][y] != '1')
        return (-1);
    if (save[x][y] == ' ' && save[x][y + 1] !=  '1')
        return(-1);
    if (save[x][y] == ' ' && save[x][y - 1] != '1')
        return (-1);
    if ((save[x][y] == '0' || save[x][y] == '2') && save[x + 1][y] == ' ')
        return -1;
    if ((save[x][y] == '0' || save[x][y] == '2') && save[x - 1][y] == ' ')
        return -1;
    if ((save[x][y] == '0' || save[x][y] == '2') && !save[x + 1][y])
        return -1;
    if ((save[x][y] == '0' || save[x][y] == '2') && !save[x - 1][y])
        return -1;
    return (0);
}

int     check_close(char **save, int size)
{
    int x;
    int y;
    int first;

    first = start_map(save);
    x = first + 1;
    while (x < (size - (counter_map(save, first, size) + 1)))
    {
        y = 1;
        while (y < ft_strlen(save[x]))
        {
            while(save[x][y] == ' ')
                y++;
            if (check_other_things(save, x, y) == -1)
                return (-1);
            if ((save[x][y] == '0' || save[x][y] == '2') && (save[x + 1][y] != '1' && save[x + 1][y] != '0' && save[x + 1][y] != '2' && save[x + 1][y] != 'W' && save[x + 1][y] != 'N' && save[x + 1][y] != 'S' && save[x + 1][y] != 'E' && !save[x + 1]))
                return (-1);
            if ((save[x][y] == '0' || save[x][y] == '2') && (save[x - 1][y] != '1' && save[x - 1][y] != '0' && save[x - 1][y] != '2' && save[x - 1][y] != 'W' && save[x - 1][y] != 'N' && save[x - 1][y] != 'S' && save[x - 1][y] != 'E' && !save[x - 1]))
                return (-1);
            y++;
        }
        x++;
    }
    return (0);
}