#include "dolar_expand.h"

int	pid = 145986;
int	error1 = 0;

void	add_pid(char *dst, char *pid, int len)
{
	int	i;
	int	pos;

	i = 0;
	pos = 0;
	while (dst[pos])
		pos ++;
	while (i < len)
	{
		dst[pos] = pid[i];
		i ++;
		pos ++;
	}
}

void	add_final(char *dst, char *str, int pos)
{
	int	i;

	i = ft_strlen(dst);
	while (str[pos])
	{
		dst[i] = str[pos];
		i ++;
		pos ++;
	}
	dst[i] = '\0';
}

char	*expand_pid(char *str, int pos)
{
	int		pid_len;
	char	*pid2;
	char	*temp;

	pid2 = ft_itoa(pid);
	pid_len = ft_strlen(pid2);
	temp = malloc(ft_strlen(str) + pid_len + 1);
	ft_strlcpy(temp, str, pos + 1);
	ft_strlcat(temp, pid2, pid_len + ft_strlen(temp) + 1);
	add_final(temp, str, pos + 2);
	free(pid2);
	free(str);
	return (temp);
}

char	*expand_error(char *str, int pos)
{
	int		error_len;
	char	*error2;
	char	*temp;

	error2 = ft_itoa(error1);

	error_len = ft_strlen(error2);
	temp = (char *)malloc(ft_strlen(str) + error_len + 1);
	ft_strlcpy(temp, str, pos + 1);
	ft_strlcat(temp, error2, error_len + ft_strlen(temp) + 1);
	add_final(temp, str, pos + 2);
	temp[pos + 2] = '\0';
	free(error2);
	free(str);
	return (temp);
}

int	check_expansion(char *name, char **env)
{
	int		i;
	char	c;

	i = 0;
	while (env[i])
	{
		c = env[i][ft_strlen(name)];
		if (!ft_strncmp(name, env[i], ft_strlen(name)) && c == '=')
			return (i);
		i ++;
	}
	return (0);
}

char	*find_word(char *str, int i)
{
	char	*dst;
	int		j;
	int		word_len;
	int		pos;

	j = 0;
	pos = i;
	word_len = 0;
	while (ft_isalnum(str[i + 1]))
	{
		i ++;
		word_len ++;
	}
	dst = malloc(word_len + 1);
	dst[0] = '\0';
	i = pos;
	while (ft_isalnum(str[i + 1]))
	{
		dst[j] = str[i + 1];
		i ++;
		j ++;
	}
	dst[j] = '\0';
	return (dst);
}

char	*find_value(char *env)
{
	int		start;
	int		end;
	char	*value;
	int		i;

	i = 0;
	start = 0;
	end = 0;
	while (env[start] != '=')
		start ++;
	while (env[end])
		end ++;
	value = malloc(end - start);
	start += 1;
	while (start < end)
	{
		value[i] = env[start];
		start ++;
		i ++;
	}
	value[i] = '\0';
	return (value);
}

char	*expanding(char *str, char *word, char *env, int pos)
{
	char	*value;
	char	*dst;

	value = find_value(env);
	dst = malloc(ft_strlen(str) + ft_strlen(value) + 1);
	ft_strlcpy(dst, str, pos + 1);
	ft_strlcat(dst, value, ft_strlen(value) + ft_strlen(dst) + 1);
	add_final(dst, str, pos + ft_strlen(word) + 1);
	free(value);
	free(str);
	return (dst);
}

char	*expand_delete(char *str, char *word, int pos)
{
	char	*dst;

	dst = malloc(ft_strlen(str) + 1);
	dst[0] = '\0';
	ft_strlcpy(dst, str, pos + 1);
	dst[pos + 1] = '\0';
	add_final(dst, str, pos + ft_strlen(word) + 1);
	free(str);
	return (dst);
}

char	*expand(char *str, int i, char **env)
{
	char	*word;
	int		line;

	word = find_word(str, i);
	line = check_expansion(word, env);
	if (line)
		str = expanding(str, word, env[line], i);
	else
		str = expand_delete(str, word, i);
	free(word);
	return (str);
}

char	*expand_loop(int i, char *str, char **env)
{
	while (str[i] == '$' && str[i + 1])
	{
		if (str[i + 1] != '$')
		{
			if (str[i + 1] == '?')
			{
				str = expand_error(str, i);
				i ++;
			}
			else
			{
				str = expand(str, i, env);
				break ;
			}
			i ++;
		}
	}
	return (str);
}

char	*dolar_expand_str(char *str, char **env)
{
	int	i;

	i = 0;
	if (str[i] == '\'')
		return (str);
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] && str[i + 1] > 32 && str[i + 1] != 34)
		{
			if (str[i + 1] && str[i + 1] == '$')
				str = expand_pid(str, i);
			else
				str = expand_loop(i, str, env);
			i = 0;
		}
		i ++;
	}
	return (str);
}

char	**dolar_expand(char **mtrx, char **env)
{
	int	i;

	i = 0;
	while (mtrx[i])
	{
		mtrx[i] = dolar_expand_str(mtrx[i], env);
		i ++;
	}
	return (mtrx);
}

int	main()
{
	char	**mtrx;
	char	**env;
	int		i = 0;


	mtrx = (char **)malloc(sizeof(char *) * 6);
	mtrx[0] = ft_strdup("echo");
	mtrx[1] = ft_strdup("$a");
	mtrx[2] = ft_strdup("noo$h $sii$?");
	mtrx[3] = ft_strdup("$?");
	mtrx[4] = ft_strdup("si");
	mtrx[5] = NULL;


	env = (char **)malloc(sizeof(char *) * 9);
	env[0] = ft_strdup("XPC_SERVICE_NAME=0");
	env[1] = ft_strdup("HOME=/Users/jelorria");
	env[2] = ft_strdup("hola__CF_hola_TEXT_ENCODING=0x18B75:0x0:0x0");
	env[3] = ft_strdup("PWD=/Users/jelorria/cursus/pipe_split2");
	env[4] = ft_strdup("VSCODE_GIT_IPC_HANDLE=/var/folders/zz/zyxvpxvq6csfxvn_n000cbfm0032vn/T/vscode-git-cb4e196c2c.sock");
	env[5] = ft_strdup("holaax=tu");
	env[6] = ft_strdup("TERM=xterm-256color");
	env[7] = ft_strdup("a=yo");
	env[8] = NULL;

	printf("%s\n\n", mtrx[2]);
	mtrx = dolar_expand(mtrx, env);
	printf("%s\n", mtrx[1]);
	printf("%s\n", mtrx[2]);
	printf("%s\n", mtrx[3]);

	ft_free(mtrx);
	ft_free(env);
}