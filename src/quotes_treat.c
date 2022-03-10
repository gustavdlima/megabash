#include "minishell.h"

// int	search_substituted_spaces(char *cmd)
// {
// 	int	spaces;
// 	int	i;

// 	i = 0;
// 	spaces = 0;
// 	while(cmd[i])
// 	{
// 		if (cmd[i] == 1)
// 			spaces++;
// 		i++;
// 	}
// 	if (spaces > 0)
// 	{
// 		printf("Tem espaço no argumento\n");
// 		return (1);
// 	}
// 	return (0);
// }

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

char	*no_quotes(char *cmd)
{
	char	*str;
	int		i;
	int		j;
	int		len;

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
