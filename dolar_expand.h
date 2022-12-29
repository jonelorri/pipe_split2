#ifndef DOLAR_EXPAND_H
# define DOLAR_EXPAND_H

#include <stdio.h>
#include <stdlib.h>

typedef struct s_expand
{

}	            t_expand;

size_t	ft_strlen(const char *str);
void	*ft_memcpy(void *dest, const void *src, size_t n);
char	*ft_strdup(const char *s);
void    ft_free(char **mtrx);
char	*ft_itoa(int n);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);

#endif