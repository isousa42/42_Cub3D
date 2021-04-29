#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>

#define BUFFERSIZE 42

int		get_next_line(int fd, char **line);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strchr(char *s, char c);
char	*ft_strdup(char *src);
char	*ft_substr(char *s, int start, int len);
int		ft_strlen(char *str);

#endif