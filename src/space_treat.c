#include "minishell.h"

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
	int		j;
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
	if (cmd[i] == cmd[cmd_size])
	{
		space_treat(cmd, cmd[i]);
		matrix = ft_split(cmd, ' ');
	}
	j = 0;
	while (matrix[j])
	{
		if (matching_quotes(matrix[j]) == 1)
		{
			printf("Aspas faltando\n");
			exit(1);
		}
		j++;
	}
	reverse_space_treat(matrix);
	return (matrix);
}
