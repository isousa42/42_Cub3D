#include "gnl.h"


int main()
{
    // SAVING ALL INFORMATION IN THE FILE IN THE MATRIX **save
    int fd;
    int ret;
    char *line;
    char **save;
    t_file file;
    int control;
    t_list *lista = NULL;

    ret = 0;
    line = NULL;
    control = 0;
    fd = open("cub3d.cub", O_RDONLY);
    while ((ret = get_next_line(fd, &line)) > 0)
    {
        if (line[0] == 'R')
        {
            parse_r(&file, line);
        }
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
            parse_f(&file, line);
        else if (line[0] == 'C')
            parse_c(&file, line);
        else
            ft_lstadd_back(&lista, ft_lstnew((void *)line));
    }
    close(fd);


    int x;
    int size;

    x = 0;
    size = ft_lstsize(lista);
    save = (char **)malloc(sizeof(char *) * size);
    while (lista != NULL)
    {
        save[x] = ft_strdup(lista->content);
        lista = lista->next;
        x++;
    }

    check_errors_map(save, size);
    


    

    return 0;
}

