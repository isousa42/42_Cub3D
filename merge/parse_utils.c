#include "cub3d.h"

void    parse_r(t_info *info, char *line)
{
    int y;
    info->width = 0;
	info->height = 0;

    y = 0;
    if (check_resolution(line) == -1)
    {
        printf("ERROR = RESOLUTION HAS A PROBLEM! CHANGE IT (please).");
        exit(0);
    }
    while (ft_isdigit(line[y]) == 0)
        y++;
    while (ft_isdigit(line[y]) == 1)
    {
        info->width = (info->width * 10) + (line[y] - '0');
        y++;
    }
    while (ft_isdigit(line[y]) == 0)
        y++;
    while (ft_isdigit(line[y]) == 1)
    {
        info->height = (info->height * 10) + (line[y] - '0');
        y++;
    }
}

void    parse_f(t_info *info, char *line)
{
    int y;

    if (check_c_f(line) == -1)
    {
        printf("ERROR = FLOOR HAS A PROBLEM! CHANGE IT (please).");
        exit(0);
    }
    y = 0;
    while (ft_isdigit(line[y]) == 0)
        y++;
    while (ft_isdigit(line[y]) == 1)
        info->r = (info->r * 10) + (line[y++] - '0');
    while (ft_isdigit(line[y]) == 0)
        y++;
    while (ft_isdigit(line[y]) == 1)
        info->g = (info->g * 10) + (line[y++] - '0');
    while (ft_isdigit(line[y]) == 0)
        y++;
    while (ft_isdigit(line[y]) == 1)
        info->b = (info->b * 10) + (line[y++] - '0');
    if (info->r > 255 || info->b > 255 || info->g > 255)
        printf("ERROR");
    info->flagF[0] = info->r;
    info->flagF[1] = info->g;
    info->flagF[2] = info->b;
}

void    parse_c(t_info *info, char *line)
{
    int y;

    if (check_c_f(line) == -1)
    {
        printf("ERROR = CEILING HAS A PROBLEM! CHANGE IT (please).");
        exit(0);
    }
    y = 0;
    while (ft_isdigit(line[y]) == 0)
        y++;
    while (ft_isdigit(line[y]) == 1)
        info->r2 = (info->r2 * 10) + (line[y++] - '0');
    while (ft_isdigit(line[y]) == 0)
        y++;
    while (ft_isdigit(line[y]) == 1)
        info->g2 = (info->g2 * 10) + (line[y++] - '0');
    while (ft_isdigit(line[y]) == 0)
        y++;
    while (ft_isdigit(line[y]) == 1)
        info->b2 = (info->b2 * 10) + (line[y++] - '0');
    if (info->r2 > 255 || info->b2 > 255 || info->g2 > 255)
        printf("ERROR");
    info->flagC[0] = info->r2;
    info->flagC[1] = info->g2;
    info->flagC[2] = info->b2;
}

void    parse_variable(t_info *info, char *line, int control)
{
    char *save;
    int y;
    

    y = 0;
    while (line[y] != ' ' || (line[y] <= 9 && line[y] >= 13))
        y++;
    while (line[y] == ' ' || (line[y] >= 9 && line[y] <= 13))
        y++;
    save = ft_substr(line, y, ft_strlen(line) - y);
    parse_flags(info, save, control);

}

void    parse_flags(t_info *info,char *save, int control)
{
    if (control == 1)
        info->flagNO = ft_strdup(save);
    else if (control == 2)
        info->flagSO = ft_strdup(save);
    else if (control == 3)
        info->flagWE = ft_strdup(save);
    else if (control == 4)
        info->flagEA = ft_strdup(save);
    else if (control == 5)
        info->flagS = ft_strdup(save);
}