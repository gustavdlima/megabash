#include "minishell.h"

int	special_or_metacharacters(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == ';' || cmd[i] == 92 || cmd[i] == '(' || cmd[i] == ')'
			|| cmd[i] == '&' || cmd[i] == '#')
			return (TRUE);
		i++;
	}
	return (FALSE);
}

// char	*interpret_dollar(char *cmd, int position)
// {
// 	char	*interpreted;
// 	int		i;
// 	int		j;
// 	int		len;

// 	i = 0;
// 	j = 0;
// 	if (cmd[position++] == '?')
// 	//tchama o valor de saída do exit
// 	len = ft_strlen(cmd); //+ ft_strlen(tamanho_da_variável_de_ambiente);
// 	interpreted = malloc(len * sizeof(char));
// 	while (cmd[i])
// 	{
// 		if (i + 1 == position)
// 		{
// 			interpreted[j++] = variavelDeAmbiente[];
// 		}
// 		interpreted[j++] = cmd[i++];
// 	}
// 	free(cmd);
// 	return (interpreted);
// }

int	unquotted_line(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == 34 || cmd[i] == 39)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

char	*metacharacters_treat(char *cmd)
{
	int	i;

	i = 0;
	if (double_closed_quotes(cmd) == TRUE)
	{
		while (cmd[i])
		{
			if (cmd[i] == 34)
			{
				i++;
				while (cmd[i] && cmd[i] != 34)
				{
					if (cmd[i] == '$')
						printf("Tem dolar entre aspas duplas, chamar função para interpretar\n");
					i++;
				}
			}
			i++;
		}
	}
	else if (unquotted_line(cmd) == TRUE)
	{
		if (special_or_metacharacters(cmd) == TRUE)
		{
			printf("Caractere especial ou metacaractere fora de aspas, NÃO PODE!\n");
		}
		while (cmd[i])
		{
			if (cmd[i] == '$')
				printf("Tem dolar fora de aspas, chamar função para interpretar\n");
			i++;
		}
	}
	return(cmd);
}

