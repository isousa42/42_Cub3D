#include "gnl.h"

int main()
{
    int fd;
    int ret;
    int x;
    char *line;
    char **save;

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
        printf("%s = %d\n", line, x);
        x++;
        free(line);
    }
    save[x] = "\0";
    // while ((ret = get_next_line(fd, &line)) > 0)
    // {
    //     printf(" \n [ Return: %d ] | A line has been read => %s\n", ret, line);
    //     free(line);
    // }
    // printf(" \n [ Return: %d ] A line has been read: %s\n", ret, line);
    // printf("\n");
    // if (ret == -1)
    //     printf("-----------\n An error happened\n");
    // else if (ret == 0)
    // {
    //     printf("-----------\n EOF has been reached\n");
    //     free(line);
    // }
    return 0;
}