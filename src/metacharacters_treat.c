#include "minishell.h"

int	special_characters(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == 59 || cmd[i] == 92)
			return (1);
		i++;
	}
	return (0);
}

// char	*interpret_dollar(char *cmd, int position)
// {
// 	char	*interpreted;
// 	int		i;
// 	int		j;
// 	 int		len;
// 	int wants_exit;

// 	i = 0;
// 	j = 0;
// 	wants_exit = position++;
// 	len = cmd + tamanho do nome do user;
// 	if (cmd[wants_exit] == '?')
// 	//tchama o valor de saída do exit
// 	while (cmd[i])
// 	{
// 		if (cmd[position])
// 		{
// 			// interpreted[j++] copiar o nome do user
// 		}
// 		interpreted[j++] = cmd[i++];
// 	}
// 	return (interpreted);
// }

char	*metacharacters_treat(char *cmd)
{
	int	i;

	i = 0;
	if (double_quotes(cmd) == 1)
	{
		while (cmd[i])
		{
			if (cmd[i] == 34)
			{
				i++;
				while (cmd[i] && cmd[i] != 34)
				{
					if (cmd[i] == 36)
						printf("Tem dolar, chamar função para interpretar\n");
					i++;
				}
			}
			i++;
		}
	}
	return(cmd);
}

