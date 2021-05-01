#include "gnl.h"

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
    save = malloc(sizeof(char *) * (34));
	if (!save)
		return (0);
    while ((ret = get_next_line(fd, &line)) > 0)
    {
        save[x] = ft_strdup(line);
        printf("%s\n", save[x]);
        x++;
        free(line);
    }
    save[x] = "\0";
    close(fd);
    

    int first = 0;
    int second = 0;
    int y;
    x = 0;

    
    y = 0;
    if (save[x][y] == 'R')
    {
        while (ft_isdigit(save[x][y]) == 0)
            y++;
        while (ft_isdigit(save[x][y]) == 1)
        {
            first = (first * 10) + (save[x][y] - '0');
            y++;
        }
        while (ft_isdigit(save[x][y]) == 0)
            y++;
        while (ft_isdigit(save[x][y]) == 1)
        {
            second = (second * 10) + (save[x][y] - '0');
            y++;
        }
    }
    file.flagRX = first;
    file.flagRY = second;
    printf("%d\n", file.flagRX);
    printf("%d\n", file.flagRY);
    x++;
    y = 0;
    char *temp;
    if (save[x][y] == 'N' && save[x][y + 1] == 'O')
    {
        while (save[x][y] != ' ' || (save[x][y] <= 9 && save[x][y] >= 13))
            y++;
        while (save[x][y] == ' ' || (save[x][y] >= 9 && save[x][y] <= 13))
            y++;
        temp = ft_substr(save[x], y, ft_strlen(save[x]) - y);
    }
    file.flagNO = ft_strdup(temp);
    printf("%s\n", file.flagNO);
    free(temp);
    x++;
    y = 0;
    if (save[x][y] == 'S' && save[x][y + 1] == 'O')
    {
        while (save[x][y] != ' ' || (save[x][y] <= 9 && save[x][y] >= 13))
            y++;
        while (save[x][y] == ' ' || (save[x][y] >= 9 && save[x][y] <= 13))
            y++;
        temp = ft_substr(save[x], y, ft_strlen(save[x]) - y);
    }
    file.flagSO = ft_strdup(temp);
    printf("%s\n", file.flagSO);
    free(temp);
    x++;
    y = 0;
    if (save[x][y] == 'W' && save[x][y + 1] == 'E')
    {
        while (save[x][y] != ' ' || (save[x][y] <= 9 && save[x][y] >= 13))
            y++;
        while (save[x][y] == ' ' || (save[x][y] >= 9 && save[x][y] <= 13))
            y++;
        temp = ft_substr(save[x], y, ft_strlen(save[x]) - y);
    }
    file.flagWE = ft_strdup(temp);
    printf("%s\n", file.flagWE);
    free(temp);
    x++;
    y = 0;
    if (save[x][y] == 'E' && save[x][y + 1] == 'A')
    {
        while (save[x][y] != ' ' || (save[x][y] <= 9 && save[x][y] >= 13))
            y++;
        while (save[x][y] == ' ' || (save[x][y] >= 9 && save[x][y] <= 13))
            y++;
        temp = ft_substr(save[x], y, ft_strlen(save[x]) - y);
    }
    file.flagEA = ft_strdup(temp);
    printf("%s\n", file.flagEA);
    free(temp);
    x++;
    y = 0;
    if (save[x][y] == 'S' && save[x][y + 1] == ' ')
    {
        while (save[x][y] != ' ' || (save[x][y] <= 9 && save[x][y] >= 13))
            y++;
        while (save[x][y] == ' ' || (save[x][y] >= 9 && save[x][y] <= 13))
            y++;
        temp = ft_substr(save[x], y, ft_strlen(save[x]) - y);
    }
    file.flagS = ft_strdup(temp);
    printf("%s\n", file.flagS);
    free(temp);
    x++;
    y = 0;
    while (ft_isalpha(save[x][y]) == 0)
        x++;
    int r = 0;
    int g = 0;
    int b = 0;
    if (save[x][y] == 'F')
    {
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
    }
    printf("%d\n", r);
    printf("%d\n", g);
    printf("%d\n", b);
    x++;
    y = 0;
    while (ft_isalpha(save[x][y]) == 0)
        x++;
    int r2 = 0;
    int g2 = 0;
    int b2 = 0;
    if (save[x][y] == 'C')
    {
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
    }
    printf("%d\n", r2);
    printf("%d\n", g2);
    printf("%d\n", b2);

    return 0;
}