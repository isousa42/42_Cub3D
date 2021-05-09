#include "gnl.h"


void    parse_variable(t_file *file, char *line, int control)
{
    char *save;
    int y;
    

    y = 0;
    while (line[y] != ' ' || (line[y] <= 9 && line[y] >= 13))
        y++;
    while (line[y] == ' ' || (line[y] >= 9 && line[y] <= 13))
        y++;
    save = ft_substr(line, y, ft_strlen(line) - y);
    parse_flags(save, file, control);

}

void    parse_flags(char *save, t_file *file, int control)
{
    if (control == 1)
        file->flagNO = save;
    else if (control == 2)
        file->flagSO = save;
    else if (control == 3)
        file->flagWE = save;
    else if (control == 4)
        file->flagEA = save;
    else if (control == 5)
        file->flagS = save;
}

int    parse_r(t_file *file, char *line)
{
    int y;

    y = 1;
    while (line[y])
    {
        if (ft_isdigit(line[y] == 0 || line[y] == ' '))
            return (-1);
        y++;
    }
    y = 0;
    while (ft_isdigit(line[y]) == 0)
        y++;
    while (ft_isdigit(line[y]) == 1)
    {
        file->flagRX = (file->flagRX * 10) + (line[y] - '0');
        y++;
    }
    while (ft_isdigit(line[y]) == 0)
        y++;
    while (ft_isdigit(line[y]) == 1)
    {
        file->flagRY = (file->flagRY * 10) + (line[y] - '0');
        y++;
    }
    
    return (0);
}

int    parse_f(t_file *file, char *line)
{
    int r = 0;
    int g = 0;
    int b = 0;
    int y;

    y = 1;
    while (line[y])
    {
        if (ft_isdigit(line[y] == 0 || line[y] == ' '))
            return (-1);
        y++;
    }
    y = 0;
    while (ft_isdigit(line[y]) == 0)
        y++;
    while (ft_isdigit(line[y]) == 1)
    {
        r = (r * 10) + (line[y] - '0');
        y++;
    }
    while (ft_isdigit(line[y]) == 0)
        y++;
    while (ft_isdigit(line[y]) == 1)
    {
        g = (g * 10) + (line[y] - '0');
        y++;
    }
    while (ft_isdigit(line[y]) == 0)
        y++;
    while (ft_isdigit(line[y]) == 1)
    {
        b = (b * 10) + (line[y] - '0');
        y++;
    }
    file->flagF[0] = r;
    file->flagF[1] = g;
    file->flagF[2] = b;
    return (0);
}

int    parse_c(t_file *file, char *line)
{
    int r2 = 0;
    int g2 = 0;
    int b2 = 0;
    int y;

    y = 1;
    while (line[y])
    {
        if (ft_isdigit(line[y] == 0 || line[y] == ' '))
            return (-1);
        y++;
    }
    y = 0;
    while (ft_isdigit(line[y]) == 0)
        y++;
    while (ft_isdigit(line[y]) == 1)
    {
        r2 = (r2 * 10) + (line[y] - '0');
        y++;
    }
    while (ft_isdigit(line[y]) == 0)
        y++;
    while (ft_isdigit(line[y]) == 1)
    {
        g2 = (g2 * 10) + (line[y] - '0');
        y++;
    }
    while (ft_isdigit(line[y]) == 0)
        y++;
    while (ft_isdigit(line[y]) == 1)
    {
        b2 = (b2 * 10) + (line[y] - '0');
        y++;
    }
    file->flagC[0] = r2;
    file->flagC[1] = g2;
    file->flagC[2] = b2;

    return (0);
}

