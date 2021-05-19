#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int ft_strlen(char *str)
{
    int i;
    i = 0;
    if (!str)
        return (0);
    while(str[i] != '\0')
        i++;
    return(i);
}

char *ft_strjoin(char *s1, char *s2)
{
    int i;
    int j;
    char *new;

    i = 0;
    j = 0;
    if (!s1)
        return (s2);
    new = (char *)malloc(sizeof(char *) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
    while (s1[i] != '\0')
    {
        new[i] = s1[i];
        i++;
    }
    
    while(s2[j] != '\0')
    {
        new[i] = s2[j];
        i++;
        j++; 
    }
    new[i] = '\0';
    
    return (new);
}

int ft_strchar(char *str)
{
    int i;

    i = 0;
    if (!str)
        return (0);
    while (str[i] != '\0')
    {
        if (str[i] == '\n')
            return(1);
        i++;
    }
    return (0);
}

char *get_line(char *save)
{
    int i;

    char *new;
    
    i = 0;

    while (save[i] && save[i] != '\n')
        i++;
    new = (char *)malloc(sizeof(char) * (i + 1));
    
    i = 0;
    while (save[i] && save[i] != '\n')
    {
        new[i] = save[i];
        i++;
    }
    new[i] = '\0';
    
    return (new);
    
}

char *get_save(char *save)
{
    int i;
    int j;
    char *new;

    
    i = 0;
    j = 0;
    while(save[i] && save[i] != '\n')
        i++;
    new = (char *)malloc(sizeof(char) * (ft_strlen(save) - i) + 1);
    i++;
    while(save[i] != '\0')
    {
        new[i] = save[j];
        j++;
        i++; 
    }
    new[i] = '\0';
    
    return (new);
}

int get_next_line(int fd, char **line)
{
    char *buff;
    int ret;
    static char *save;
    ret = 1;
    
    buff = (char *)malloc(sizeof(char) * 1 + 1);
    while(!ft_strchar(save) && ret != 0)
    {
        
        if ((ret = read(fd, buff, 1)) == -1)
        {
            
            free(save);
            return(-1);
        }
        buff[ret] = '\0';
        //printf("%s\n", buff);
        if (!save)
            save = "\0";
        save = ft_strjoin(save, buff);
    }
    
    free(buff);
    
    *line = get_line(save);
    save = get_save(save);
    //printf("%s\n", save);
    if(ret == 0)
        return (0);
    return (1);

}




int main()
{
    int fd;
    char *line;
    int r;

    fd = open("text.txt", O_RDONLY);
    while ((r = get_next_line(fd, &line)) > 0)
    {
        printf("%s\n", line);
        free(line);
        line = NULL;        
    }
    printf("%s\n", line);
    free(line);
    
    close(fd);

    return 0;
}