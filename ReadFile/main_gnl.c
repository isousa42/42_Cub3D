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
    int control;
    t_list *lista = NULL;



    x = 0;
    ret = 0;
    line = NULL;
    control = 0;
    fd = open("cub3d.cub", O_RDONLY);
    save = (char **)malloc(sizeof(char *) * (40));
	if (!save)
		return (0);
    while ((ret = get_next_line(fd, &line)) > 0)
    {
        if (line[0] == 'R')
            control = parse_r(&file, line);
        else if (line[0] == 'N' && line[1] == 'O')
            parse_variable(&file, line, 1);
        else if (line[0] == 'S' && line[1] == 'O')
            parse_variable(&file, line, 2);
        else if (line[0] == 'W' && line[1] == 'E')
            parse_variable(&file, line, 3);
        else if (line[0] == 'E' && line[1] == 'A')
            parse_variable(&file, line, 4);
        else if (line[0] == 'S' && line[1] == ' ')
            parse_variable(&file, line, 5);
        else if (line[0] == 'F')
            control = parse_f(&file, line);
        else if (line[0] == 'C')
            control = parse_c(&file, line);
        else
            ft_lstadd_back(&lista, ft_lstnew((void *)line));
    }

    close(fd);
    int y;
    int size = ft_lstsize(lista);
    save = (char **)malloc(sizeof(char *) * size);
    while (lista != NULL)
    {
        save[x] = ft_strdup(lista->content);
        lista = lista->next;
        x++;
    }

    x = 0;
    int z = 0;
    while (x < size)
    {
        y = 0;
        while (y < ft_strlen(save[x]))
        {
            if (x == 0 || y == 0)
            {
                if (ft_iswall(save[x][y]) == 0)
                    printf("ERROR");
                if (save[x][y] == ' ')
                {
                    z = 0;
                    while (save[x][z] == ' ')
                        z++;
                    if (save[x][z] != '1')
                        printf("ERROR");
                }
            }
            y++;
        }
        x++;
    }





    return 0;
}