#include "gnl.h"


// void    parse_variable(t_file *file, char *line, int control)
// {
//     char *save;
//     int y;
    

//     y = 0;
//     while (line[y] != ' ' || (line[y] <= 9 && line[y] >= 13))
//         y++;
//     while (line[y] == ' ' || (line[y] >= 9 && line[y] <= 13))
//         y++;
//     save = ft_substr(line, y, ft_strlen(line) - y);
//     parse_flags(save, file, control);

// }

// void    parse_flags(char *save, t_file *file, int control)
// {
//     if (control == 1)
//         file->flagNO = save;
//     else if (control == 2)
//         file->flagSO = save;
//     else if (control == 3)
//         file->flagWE = save;
//     else if (control == 4)
//         file->flagEA = save;
//     else if (control == 5)
//         file->flagS = save;
// }

// void    parse_r(t_file *file, char *line)
// {
//     int y;

//     y = 0;
//     check_resolution(line);
//     while (ft_isdigit(line[y]) == 0)
//         y++;
//     while (ft_isdigit(line[y]) == 1)
//     {
//         file->flagRX = (file->flagRX * 10) + (line[y] - '0');
//         y++;
//     }
//     while (ft_isdigit(line[y]) == 0)
//         y++;
//     while (ft_isdigit(line[y]) == 1)
//     {
//         file->flagRY = (file->flagRY * 10) + (line[y] - '0');
//         y++;
//     }
// }

// void    parse_f(t_file *file, char *line)
// {
//     int r = 0;
//     int g = 0;
//     int b = 0;
//     int y;

//     check_c_f(line);
//     y = 0;
//     while (ft_isdigit(line[y]) == 0)
//         y++;
//     while (ft_isdigit(line[y]) == 1)
//     {
//         r = (r * 10) + (line[y] - '0');
//         y++;
//     }
//     while (ft_isdigit(line[y]) == 0)
//         y++;
//     while (ft_isdigit(line[y]) == 1)
//     {
//         g = (g * 10) + (line[y] - '0');
//         y++;
//     }
//     while (ft_isdigit(line[y]) == 0)
//         y++;
//     while (ft_isdigit(line[y]) == 1)
//     {
//         b = (b * 10) + (line[y] - '0');
//         y++;
//     }
//     if (r > 255 || b > 255 || g > 255)
//         printf("ERROR");
//     file->flagF[0] = r;
//     file->flagF[1] = g;
//     file->flagF[2] = b;
// }

// void    parse_c(t_file *file, char *line)
// {
//     int r = 0;
//     int g = 0;
//     int b = 0;
//     int y;

//     check_c_f(line);
//     y = 0;
//     while (ft_isdigit(line[y]) == 0)
//         y++;
//     while (ft_isdigit(line[y]) == 1)
//     {
//         r = (r * 10) + (line[y] - '0');
//         y++;
//     }
//     while (ft_isdigit(line[y]) == 0)
//         y++;
//     while (ft_isdigit(line[y]) == 1)
//     {
//         g = (g * 10) + (line[y] - '0');
//         y++;
//     }
//     while (ft_isdigit(line[y]) == 0)
//         y++;
//     while (ft_isdigit(line[y]) == 1)
//     {
//         b = (b * 10) + (line[y] - '0');
//         y++;
//     }
//     if (r > 255 || b > 255 || g > 255)
//         printf("ERROR");
//     file->flagC[0] = r;
//     file->flagC[1] = g;
//     file->flagC[2] = b;
// }

// SEG FAULT IF NOT 3 NUMBERS IN THE C FLAG ON THE FILE ! DONT KNOW WHY...

