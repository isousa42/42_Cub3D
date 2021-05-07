#include "gnl.h"

void    parse_r(t_file *file, char **save, int x, int y)
{
    while (ft_isdigit(save[x][y]) == 0)
        y++;
    while (ft_isdigit(save[x][y]) == 1)
    {
        file->flagRX = (file->flagRX * 10) + (save[x][y] - '0');
        y++;
    }
    while (ft_isdigit(save[x][y]) == 0)
        y++;
    while (ft_isdigit(save[x][y]) == 1)
    {
        file->flagRY = (file->flagRY * 10) + (save[x][y] - '0');
        y++;
    }

    printf("%d\n", file->flagRX);
    printf("%d\n", file->flagRY);
}

void    parse_no(t_file *file, char **save, int x, int y)
{
    while (save[x][y] != ' ' || (save[x][y] <= 9 && save[x][y] >= 13))
        y++;
    while (save[x][y] == ' ' || (save[x][y] >= 9 && save[x][y] <= 13))
        y++;
    file->flagNO = ft_substr(save[x], y, ft_strlen(save[x]) - y);

    printf("%s\n", file->flagNO);
}

void    parse_so(t_file *file, char **save, int x, int y)
{
    while (save[x][y] != ' ' || (save[x][y] <= 9 && save[x][y] >= 13))
        y++;
    while (save[x][y] == ' ' || (save[x][y] >= 9 && save[x][y] <= 13))
        y++;
    file->flagSO = ft_substr(save[x], y, ft_strlen(save[x]) - y);

    printf("%s\n", file->flagSO);
}

void    parse_we(t_file *file, char **save, int x, int y)
{
    while (save[x][y] != ' ' || (save[x][y] <= 9 && save[x][y] >= 13))
        y++;
    while (save[x][y] == ' ' || (save[x][y] >= 9 && save[x][y] <= 13))
        y++;
    file->flagWE = ft_substr(save[x], y, ft_strlen(save[x]) - y);

    printf("%s\n", file->flagWE);
}

void    parse_ea(t_file *file, char **save, int x, int y)
{
    while (save[x][y] != ' ' || (save[x][y] <= 9 && save[x][y] >= 13))
        y++;
    while (save[x][y] == ' ' || (save[x][y] >= 9 && save[x][y] <= 13))
        y++;
    file->flagEA = ft_substr(save[x], y, ft_strlen(save[x]) - y);

    printf("%s\n", file->flagEA);
}

void    parse_s(t_file *file, char **save, int x, int y)
{
    while (save[x][y] != ' ' || (save[x][y] <= 9 && save[x][y] >= 13))
        y++;
    while (save[x][y] == ' ' || (save[x][y] >= 9 && save[x][y] <= 13))
        y++;
    file->flagS = ft_substr(save[x], y, ft_strlen(save[x]) - y);

    printf("%s\n", file->flagS);
}

void    parse_f(t_file *file, char **save, int x, int y)
{
    int r = 0;
    int g = 0;
    int b = 0;

    while (ft_isdigit(save[x][y]) == 0)
        y++;
    while (ft_isdigit(save[x][y]) == 1)
    {
        r = (r * 10) + (save[x][y] - '0');
        y++;
    }
    while (ft_isdigit(save[x][y]) == 0)
        y++;
    while (ft_isdigit(save[x][y]) == 1)
    {
        g = (g * 10) + (save[x][y] - '0');
        y++;
    }
    while (ft_isdigit(save[x][y]) == 0)
        y++;
    while (ft_isdigit(save[x][y]) == 1)
    {
        b = (b * 10) + (save[x][y] - '0');
        y++;
    }
    file->flagF[0] = r;
    file->flagF[1] = g;
    file->flagF[2] = b;

    printf("%d\n", file->flagF[0]);
    printf("%d\n", file->flagF[1]);
    printf("%d\n", file->flagF[2]);
}

void    parse_c(t_file *file, char **save, int x, int y)
{
    int r2 = 0;
    int g2 = 0;
    int b2 = 0;
    while (ft_isdigit(save[x][y]) == 0)
        y++;
    while (ft_isdigit(save[x][y]) == 1)
    {
        r2 = (r2 * 10) + (save[x][y] - '0');
        y++;
    }
    while (ft_isdigit(save[x][y]) == 0)
        y++;
    while (ft_isdigit(save[x][y]) == 1)
    {
        g2 = (g2 * 10) + (save[x][y] - '0');
        y++;
    }
    while (ft_isdigit(save[x][y]) == 0)
        y++;
    while (ft_isdigit(save[x][y]) == 1)
    {
        b2 = (b2 * 10) + (save[x][y] - '0');
        y++;
    }
    file->flagC[0] = r2;
    file->flagC[1] = g2;
    file->flagC[2] = b2;


    printf("%d\n", file->flagC[0]);
    printf("%d\n", file->flagC[1]);
    printf("%d\n", file->flagC[2]);
}

int     count_lines_map(char **save, int x)
{
    int counter;

    counter = 0;
    while (save[x])
    {
        counter++;
        x++;
    }
    return (counter);
}

void   parse_map(t_file *file, char **save, int x)
{
    char **map;
    int i;

    i = 0;
    map = (char **)malloc(sizeof(char *) * count_lines_map(save, x));
    while (save[x])
    {
        map[i] = ft_strdup(save[x]);
        printf("%s\n", map[i]);
        x++;
        i++;
    }
}