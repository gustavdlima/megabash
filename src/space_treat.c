#include "minishell.h"

int	search_quotes(char *cmd)
{
	int	i;

	i = ft_strlen(cmd) - 1;
	if (cmd[0] == 39 || cmd[0] == 34)
	{
		// printf("i : %c\nj : %c\n", i);
		if (cmd[0] != cmd[i])
		{
			printf("ASPAS DIFERENTES, BOY\n");
			return (1);
		}
	}
	else if (cmd[i] == 39 || cmd[i] == 34)
	{
		if (cmd[0] != cmd[i])
		{
			printf("ASPAS DIFERENTES, BOY\n");
			return (1);
		}
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
			while (cmd[i] != sign && cmd[i])
			{
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
			break ;
		}
		i++;
	}
	(void)cmd_size;
	if (cmd[i] == cmd[cmd_size])
	{
		space_treat(cmd, cmd[i]);
		matrix = ft_split(cmd, ' ');
	}
	int		j;
	j = 0;
	while (matrix[j])
	{
		if (search_quotes(matrix[j]) == 1)
			exit(1);
		// if (j > 0 && multiple_quotes(matrix[j]) == 1)
		// 	exit(1);
		j++;
	}
	reverse_space_treat(matrix);
	return (matrix);
}
