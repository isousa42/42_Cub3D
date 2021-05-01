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

}       t_file;

int		get_next_line(int fd, char **line);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strchr(char *s, char c);
char	*ft_strdup(char *src);
char	*ft_substr(char *s, int start, int len);
int		ft_strlen(char *str);
int     ft_isdigit(int c);
int     ft_isalpha(int c);

#endif