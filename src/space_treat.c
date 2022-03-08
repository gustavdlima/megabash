#include "minishell.h"

// char	*original_cmd(char *cmd)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	j = ft_strlen(cmd);
// 	while (i < j)
// 	{
// 		if (cmd[i] == '\'')
// 		{
// 			i++;
// 			while (cmd[i] != '\'' && cmd[i] != '\0')
// 			{
// 				if (cmd[i] == 1)
// 					cmd[i] = ' ';
// 				i++;
// 			}
// 		}
// 		if (cmd[i] == '\"')
// 		{
// 			i++;
// 			while (cmd[i] != '\"' && cmd[i] != '\0')
// 			{
// 				if (cmd[i] == 1)
// 					cmd[i] = ' ';
// 				i++;
// 			}
// 		}
// 		i++;
// 	}
// 	return (cmd);
// }

// char	*treating_cmd(char *cmd)
// {
// 	int	i;

// 	i = 0;
// 	while (cmd[i])
// 	{
// 		printf("KKKKKKKKKKKKKKKKKKKKK\n");
// 		if (cmd[i] == '\'')
// 		{
// 			i++;
// 			while (cmd[i] != '\'' && cmd[i] != '\0')
// 			{
// 				if (cmd[i] == ' ')
// 					cmd[i] = 1;
// 				i++;
// 			}
// 		}
// 		if (cmd[i] == '\"')
// 		{
// 			i++;
// 			while (cmd[i] != '\"' && cmd[i] != '\0')
// 			{
// 				if (cmd[i] == ' ')
// 					cmd[i] = 1;
// 				i++;
// 			}
// 		}
// 		i++;
// 	}
// 	return (cmd);
// }

// char	**space_treat(char *input)
// {
// 	char	**cmd;
// 	char	*to_treat;
// 	int		i;

// 	i = 0;
// 	to_treat = treating_cmd(input);
// 	cmd = ft_split(to_treat, ' ');
// 	if (!cmd)
// 		perror("Failed to process the command");
// 	while (cmd[i])
// 	{
// 		cmd[i] = original_cmd(cmd[i]);
// 		i++;
// 	}
// 	return(cmd);
// }

char    *no_quotes(char *cmd)
{
    char    *str;
    int        i;
    int        j;
    int        len;

    i = 0;
    j = 0;
    len = ft_strlen(cmd) - 1;
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
				i++;
			while (cmd[i] != sign)
			{
				if (cmd[i] == '\0')
				{
					printf("\nDEU NULO PO KKKKKK\n");
					exit(130); //verificar depois!!!
				}
				else if (cmd[i] == ' ')
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
	if (cmd[i] == cmd[cmd_size])
	{
		matrix = ft_split(cmd, ' ');
	}
	return (matrix);
}
