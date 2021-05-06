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
        if (save[x][y] == 'N' && save[x][y + 1] == 'O')
            parse_no(file, save, x, y);
        if (save[x][y] == 'S' && save[x][y + 1] == 'O')
            parse_so(file, save, x, y);
        if (save[x][y] == 'W' && save[x][y + 1] == 'E')
            parse_we(file, save, x, y);
        if (save[x][y] == 'E' && save[x][y + 1] == 'A')
            parse_ea(file, save, x, y);
        if (save[x][y] == 'S' && save[x][y + 1] == ' ')
            parse_s(file, save, x, y);
        if (save[x][y] == 'F')
            parse_f(file, save, x, y);
        if (save[x][y] == 'C')
            parse_c(file, save, x, y);
        if (save[x][y] == '1')
        {
            parse_map(file, save, x, y);
            break ;
        }
        if (save[x] == 0)
            break;
        else 
        {
            if (save[x][y] == ' ')
                while (save[x][y] == ' ')
                    y++;
            else
            {
                x++;
                y = 0;
            }
        }
    }
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
    save = (char **)malloc(sizeof(char *) * (34));
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

    parse_file(&file, save);
    return 0;
}