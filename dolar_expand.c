#include "dolar_expand.h"

int pid = 145986;
int error1 = 0;

void add_pid(char *dst, char *pid, int len)
{
    int i;
    int pos;

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

void add_final(char *dst, char *str, int pos)
{
    int i;

    i = ft_strlen(dst);
    while (str[pos])
    {
        dst[i] = str[pos];
        i ++;
        pos ++;
    }
    dst[i] = '\0';
}

char *expand_pid(char *str, int pos)
{
    int pid_len;
    char *pid2;
    char *temp;

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

char *expand_error(char *str, int pos)
{
    int error_len;
    char *error2;
    char *temp;
    int i;

    i = 0;
    error2 = ft_itoa(error1);
    error_len = ft_strlen(error2);

    temp = malloc(ft_strlen(str) + error_len + 1);
    ft_strlcpy(temp, str, pos + 1);
    ft_strlcat(temp, error2, error_len + ft_strlen(temp) + 1);
    add_final(temp, str, pos + 2);

    free(error2);
    free(str);
    return (temp);
}

char *expand(char *str, int i)
{
    str[i] = 'Z';
    return (str);
}

char *dolar_expand(char *str, char **env)
{
    int i;

    i = 0;
    if (str[i] == '\'')
        return (str);
    while (str[i])
    {
        if (str[i] == '$' && str[i + 1] && str[i + 1] > 32 && str[i + 1] != 34)
        {
            if (str[i + 1] == '$')
            {
                str = expand_pid(str, i);
            }
            else
            {
                while (str[i + 1] && str[i + 1] != '$')
                {
                    if (str[i + 1] == '?')
                    {
                        str = expand_error(str, i);
                        i ++;
                    }
                    else
                    {
                        str = expand(str, i);
                        break ;
                    }
                    i ++;
                }
            }
            i = 0;
        }
        i ++;
    }
    return (str);
}

int main()
{
	char **mtrx;
	char **env;
	int i = 0;


	mtrx = (char **)malloc(sizeof(char *) * 6);
	mtrx[0] = ft_strdup("echo");
	mtrx[1] = ft_strdup("-n");
	mtrx[2] = ft_strdup("\"$holaax $ $$ $? $si $\"");
	mtrx[3] = ft_strdup("$");
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
	mtrx[2] = dolar_expand(mtrx[2], env);
    printf("\n%s\n", mtrx[2]);

    ft_free(mtrx);
    ft_free(env);
}