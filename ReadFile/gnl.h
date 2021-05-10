#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

typedef struct s_file
{
    int     flagRX;
    int     flagRY;
    char    *flagNO;
    char    *flagSO;
    char    *flagWE;
    char    *flagEA;
    char    *flagS;
    int     flagF[3];
    int     flagC[3];
    int     **map;

}       t_file;

typedef struct s_list
{
    void *content;
    struct s_list *next;

}       t_list;


int		get_next_line(int fd, char **line);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strchr(char *s, char c);
char	*ft_strdup(char *src);
char	*ft_substr(char *s, int start, int len);
int		ft_strlen(char *str);
int     ft_isdigit(int c);
int     ft_isalpha(int c);
int     ft_iswall(char c);

//parse_utils.c
int    parse_r(t_file *file, char *line);
void    parse_variable(t_file *file, char *line, int control);
void    parse_flags(char *save, t_file *file, int control);
int    parse_f(t_file *file, char *line);
int    parse_c(t_file *file, char *line);

//check_errors.c
int     check_sides_one(char **save, int size);
int     check_inside(char **save, int size);
int     check_letters(char **save, int size);
int     check_close(char **save, int size);

// list_utils.c
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstnew(void *content);
int	ft_lstsize(t_list *lst);

#endif