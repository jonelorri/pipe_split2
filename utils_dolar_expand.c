#include "dolar_expand.h"

size_t	ft_strlen(const char *str)
{
	size_t i;
	
	i = 0;
	while (str[i] != '\0')
		i++;
	return(i);
}

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	a;
	size_t	i;

	if (size <= ft_strlen(dest))
		return (size + ft_strlen(src));
	a = ft_strlen(dest);
	i = 0;
	while (src[i] != '\0' && a + 1 < size)
	{
		dest[a] = src[i];
		a++;
		i++;
	}
	dest[a] = '\0';
	return (ft_strlen(dest) + ft_strlen (&src[i]));
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	if (src == NULL || dst == NULL)
		return (0);
	i = 0;
	if (dstsize != 0)
	{
		while (src[i] != '\0' && i < (dstsize - 1))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (ft_strlen(src));
}

int	len(long m)
{
	int	lens;

	lens = 0;
	if (m <= 0)
		lens = 1;
	while (m != 0)
	{
		lens++;
		m = m / 10;
	}
	return (lens);
}

char	*ft_itoa(int n)
{
	char	*s;
	int	i;
	long	m;

	m = n;
	i = len(m);
	s = (char *)malloc(sizeof(char) * (i + 1));
	if (!s)
		return (NULL);
	s[i--] = '\0';
	if (m == 0)
		s[0] = '0';
	if (m < 0 )
	{
		s[0] = '-';
		m = m * -1;
	}
	while (m > 0)
	{
		s[i] = '0' + (m % 10);
		m = m / 10;
		i--;
	}
	return (s);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*ptr;
	const unsigned char	*ptr2;

	ptr = (unsigned char *)dest;
	ptr2 = (unsigned char *)src;
	while (n-- > 0)
		*(ptr++) = *(ptr2++);
	return (dest);
}

char	*ft_strdup(const char *s)
{
	char	*dest;

	dest = (char *)malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!dest)
		return (NULL);
	ft_memcpy(dest, s, ft_strlen(s));
	*(dest + ft_strlen(s)) = '\0';
	return (dest);
}

void    ft_free(char **mtrx)
{
    int i;
    
    i = 0;
    while (mtrx[i])
    {
        free(mtrx[i]);
        i ++;
    }
    free(mtrx);
}