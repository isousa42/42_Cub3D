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

    int error_side;
    int error_inside;
    int counter_letters;
    int error_close;

    error_side = check_sides_one(save, size);
    printf("ERROR SIDE = %d\n", error_side);

    error_inside = check_inside(save, size);
    printf("ERROR INSIDE = %d\n", error_inside);

    counter_letters = check_letters(save, size);
    printf("COUNTER = %d\n", counter_letters);

    error_close = check_close(save, size);
    printf("ERROR CLOSE = %d\n", error_close);
    
    return 0;
}

