#include "minishell.h"

int	search_quotes(char *cmd)
{
    int        i;
    char    signal;

    i = 0;
    signal = 0;
    while (cmd[i])
    {
        if (cmd[i] == 39 || cmd[i] == 34)
        {
            signal = cmd[i];
            i++;
        }
        while (cmd[i] != signal)
        {
            if (cmd[i] == '\0')
                break ;
            i++;
        }
        if (signal != 0 && cmd[i] != signal)
            return (1);
        signal = 0;
        i++;
    }
    return (0);
}

char    *no_quotes(char *cmd)
{
    char    *str;
    int        i;
    int        j;
    int        len;

    i = 0;
    j = 0;
    len = ft_strlen(cmd) - 1;
	printf(">>>>>>>>%s\n", cmd);
    while (cmd[i])
    {
        if (cmd[i] == '\'' || cmd[i] == '\"')
        {
            i++;
            str = ft_calloc(len, sizeof(char));
            while (i < len)
            {
                str[j++] = cmd[i++];
            }
            return (str);
        }
        i++;
    }
    return (cmd);
}

char	**reverse_space_treat(char **matrix)
{
	int	i;
	int	j;

	i = 0;
	while (matrix[i])
	{
		j = 0;
		while (matrix[i][j])
		{
			if (matrix[i][j] == 1)
			{
				matrix[i][j] = ' ';
			}
			j++;
		}
		i++;
	}
	return (matrix);
}

char	*space_treat(char *cmd, char sign)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] != sign)
		{
			if (cmd[i] == 39 || cmd[i] == 34)
				sign = cmd[i];
		}
		if (cmd[i] == sign)
		{
			i++;
			if (cmd[i] == sign)
			{
				break ;
				i++;
			}
			while (cmd[i] != sign)
			{
				// if (cmd[i] == '\0')
				// {
				// 	printf("\nDEU NULO PO KKKKKK\n");
				// 	exit(130); //verificar depois!!!
				// }
				if (cmd[i] == ' ')
					cmd[i] = 1;
				i++;
			}
		}
		i++;
	}
	return (cmd);
}

char	**matrix_split(char *cmd, int cmd_size)
{
	int		i;
	char	**matrix;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == 39 || cmd[i] == 34)
		{
			space_treat(cmd, cmd[i]);
			matrix = ft_split(cmd, ' ');
			reverse_space_treat(matrix);
			break ;
		}
		i++;
	}
	(void)cmd_size;
	if (cmd[i] == cmd[cmd_size])
		matrix = ft_split(cmd, ' ');
	return (matrix);
}
