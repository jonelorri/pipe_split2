#include <stdio.h>
#include <stdlib.h>

// size_t	ft_strlen(const char *str)
// {
// 	size_t i;
	
// 	i = 0;
// 	while (str[i] != '\0')
// 		i++;
// 	return(i);
// }

int open_pipes(char *str)
{
	int		i;

	i = 0;
	while (str[i])
		i ++;
	if (i > 0 && (str[0] == '|' || str[i - 1] == '|'))
		return(0);
	i = 0;
    if (str[i] == ' ')
    {
        while (str[i] == ' ')
        {
            i ++;
            if (str[i] == '|')
                return(0);
        }
    }
    i = 0;
	while (str[i])
	{
		if (str[i] == '|')
		{
			i ++;
			while (str[i] == ' ')
				i ++;
		}
		if (!str[i])
			return(0);
		i ++;
	}
	return(1);
}

int open_quotes(char *str)
{
	int		i;
	int		check;
	char	quote;

	i = 0;
	check = 1;
	quote = 'x';
	while (str[i])
	{
		if (str[i] == '\'' && quote != 'd')
		{
			quote = 's';
			check = check * -1;
		}
		else if (str[i] == '\"' && quote != 's')
		{
			quote = 'd';
			check = check * -1;
		}
		if (check == 1)
			quote = 'x';
		i ++;
	}
	if (!open_pipes(str))
		return(-1);
	return(check);
}

int change_caracter(char *str, char caracter)
{
	int		i;
	int		check;
	char	quote;
	int		pipes;

	pipes = 0;
	i = 0;
	check = 1;
	quote = 'x';
	while (str[i])
	{
		if (str[i] == '\'' && quote != 'd')
		{
			quote = 's';
			check = check * -1;
		}
		else if (str[i] == '\"' && quote != 's')
		{
			quote = 'd';
			check = check * -1;
		}
		if (check == 1)
			quote = 'x';
		if (str[i] == caracter && quote == 'x')
		{
			if (str[i + 1] == caracter)
			{
				printf("Minishell: Syntax error\n");
				return (-1);
			}
			pipes ++;
			str[i] = caracter -128;
		}
		i ++;
	}
	return(pipes);
}

int change_caracter2(char *str)
{
	int		i;
	int		check;
	char	quote;
	int		pipes;

	pipes = 0;
	i = 0;
	check = 1;
	quote = 'x';
	while (str[i])
	{
		if (str[i] == '\'' && quote != 'd')
		{
			quote = 's';
			check = check * -1;
		}
		else if (str[i] == '\"' && quote != 's')
		{
			quote = 'd';
			check = check * -1;
		}
		if (check == 1)
			quote = 'x';
		if (str[i] == ' ' && quote == 'x')
		{
			pipes ++;
			str[i] = ' ' -128;
		}
		i ++;
	}
	return(pipes);
}

int change_caracter_q(char *str)
{
	int		i;
	int		check;
	char	quote;
	int		num;

	num = 0;
	i = 0;
	check = 1;
	quote = 'x';
	while (str[i])
	{
		if (str[i] == '\'' && quote != 'd')
		{
			num ++;
			quote = 's';
			check = check * -1;
			str[i] = -128;
		}
		else if (str[i] == '\"' && quote != 's')
		{
			num ++;
			quote = 'd';
			check = check * -1;
			str[i] = -128;
		}
		if (check == 1)
			quote = 'x';
		i ++;
	}
	return(num);
}

int	check_mtrx_pipe(char **mtrx)
{
	int	i;
	int j;
	int flag;
	int word;

	word = 0;
	flag = 0;
	j = 0;
	i = 0;
	while (mtrx[i])
	{
		while (mtrx[i][j])
		{
			if (mtrx[i][j] > 32)
				flag = 1;
			j ++;
		}
		if (flag == 1)
			word ++;
		flag = 0;
		j = 0;
		i ++;
	}
	if (word == i)
		return (0);
	// i = 0;
	// while (mtrx[i])
	// {
	// 	free(mtrx[i]);
	// 	i ++;
	// }
	// free(mtrx);
	printf("Minishell: Syntax error\n");
	return (1);
}

size_t	ft_strlen(const char *str)
{
	size_t i;
	
	i = 0;
	while (str[i] != '\0')
		i++;
	return(i);
}

char	**ft_free(char **d, size_t start)
{
	size_t	j;

	if (d)
	{
		j = 0;
		while (j < start)
		{
			if (d[j] != NULL)
				free(d[start]);
			start++;
		}
		free(d);
	}
	return (NULL);
}

size_t	ft_lines(const char *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		while (s[i] != c && s[i] != '\0')
			i++;
		count++;
	}
	if (s[i - 1] == c)
		count--;
	return (count);
}

size_t	ft_wc(const char *s, char c)
{
	size_t	count;

	count = 0;
	while (*s != c && *s != '\0')
	{
		s++;
		count++;
	}
	return (count);
}

char	**ft_fill(char **dest, const char *s, char to_find)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (*s != '\0')
	{
		while (*s == to_find && *s != '\0')
			s++;
		if (*s == '\0')
			continue ;
		dest[i] = malloc(sizeof(char) * ft_wc(s, to_find) + 1);
		if (dest[i] == NULL)
			return (ft_free(dest, i));
		j = 0;
		while (*s != to_find && *s != '\0')
		{
			dest[i][j] = *s;
			j++;
			s++;
		}
		dest[i][j] = '\0';
		i++;
	}
	dest[i] = NULL;
	return (dest);
}

char	**ft_split(char const *s, char c)
{
	char	**dest;

	if (!s)
		return (NULL);
	if (ft_strlen(s) > 0)
		dest = malloc(sizeof(char *) * (ft_lines(s, c) + 1));
	else
		dest = malloc(sizeof(char *) * (0 + 1));
	if (dest == NULL)
		return (NULL);
	ft_fill(dest, s, c);
	return (dest);
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

char	*ft_replace(char *str, char caracter)
{
	char *dest;
	int i;
	int j;

	i = ft_strlen(str);
	dest = (char *)malloc(sizeof(char) * (i + 1));
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != caracter)
		{
			dest[j] = str[i];
			j ++;
		}
		i++;
	}
	dest[j] = '\0'; 
	return(dest);
}

char	**ft_split_pipes(char *str)
{
	int caracter_value;
	char **splited_argv;

	caracter_value = change_caracter(str, '|');
	if (caracter_value < 0)
		return (0);
	else if (caracter_value > 0)
	{
		splited_argv = ft_split(str, '|' -128);
		if(check_mtrx_pipe(splited_argv))
			return (splited_argv);
	}
	else
		splited_argv = NULL;
	return(splited_argv);
}

char	**ft_split_quotes(char *str)
{
	int caracter_value;
	char **splited_argv;
	char *new_str;

	caracter_value = change_caracter2(str);
	printf("%s\n", str);
	printf("%d\n", caracter_value);
	printf("--------\n");
	// new_str = ft_replace(str, ' ' -128);
	// printf("%s\n", new_str);
	// caracter_value = change_caracter_q(new_str);
	if (caracter_value > 0)
	{
		splited_argv = ft_split(str, ' ' -128);
		if(check_mtrx_pipe(splited_argv))
		{
			splited_argv[0][0] = -12;
			return (splited_argv);
		}
	}
	else
		splited_argv = NULL;
	return(splited_argv);
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

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	dest = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, s1, s1_len + 1);
	ft_strlcat(&dest[s1_len], s2, s2_len + 1);
	return (dest);
}


//todo: tiene que borrar comillas que no estén dentro de comillas
void    dequoter(char **mtrx) //todo: mezclar con dequoter
{
    int i;
	int len;
    char **tempM;

	len = 0;
    i = 0;
    while (mtrx[i])
    {
		if (change_caracter_q(mtrx[i]))
		{
			tempM = ft_split(mtrx[i], -128);
			mtrx[i][0] = '\0';
			while (tempM[len])
			{
				mtrx[i] = ft_strjoin(mtrx[i], tempM[len]);
				free(tempM[len]);
				len ++;
			}
			free(tempM);
			len = 0;
		}
		printf("%s\n", mtrx[i]);
        i ++;
    }
}

int main()
{
	char str[40];
	char **splited_argv;
	char **splited_argv2;
	int i = 0;

	ft_memcpy(str, "echo -n \'w\"c\'hola", 19);
	if (open_quotes(str) < 0)
	{
		printf("Minishell: Syntax error\n");
		return (0);
	}
	else
	{
		splited_argv2 = ft_split_quotes(str);
		if (splited_argv2[0][0] == -12)
		{
			return(0);
		}
		if (splited_argv2)
		{
			dequoter(splited_argv2);
			while(splited_argv2[i])
			{
				free(splited_argv2[i]);
				i ++;
			}
			free(splited_argv2);
		}

	}


	// //Split Comillas
	// splited_argv2 = ft_split_quotes(str);
	// if (!splited_argv2)
	// 	printf("NO habia quotes\n");


	// // print matrix
	// if (splited_argv)
	// {
	// 	while(splited_argv[i])
	// 	{
	// 		printf("%s\n", splited_argv[i]);
	// 		free(splited_argv[i]);
	// 		i ++;
	// 	}
	// 	free(splited_argv);
	// }
	// if (splited_argv2)
	// {
	// 	while(splited_argv[i])
	// 	{
	// 		printf("%s\n", splited_argv[i]);
	// 		free(splited_argv[i]);
	// 		i ++;
	// 	}
	// 	free(splited_argv2);
	// }
	return (0);
}