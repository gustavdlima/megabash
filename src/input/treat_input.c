#include "minishell.h"

void	treat_quote(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\'')
		{
			i++;
			while (cmd[i] != '\'')
			{
				if (cmd[i] == '\"')
					cmd[i] = 2;
				i++;
			}
		}
		if (cmd[i] == '\"')
		{
			i++;
			while (cmd[i] != '\"')
			{
				if (cmd[i] == '\'')
					cmd[i] = 3;
				i++;
			}
		}
		i++;
	}
}

void	treat_space(char *cmd)
{
	int	i;
	int	sign;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\'' || cmd[i] == '\"')
		{
			sign = cmd[i];
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
}

// void	*interpret_dollar(char *cmd)
// {

// }

// void	*treat_dollar(char *cmd)
// {
// 	int	i;

// 	i = 0;
// 	while (cmd[i])
// 	{
// 		if (cmd[i] == '\"')
// 		{
// 			i++;
// 			while (cmd[i] && cmd[i] != '\"')
// 			{
// 				if (cmd[i] == '$')
// 					printf("Tem dolar, chamar função para interpretar\n");
// 				i++;
// 			}
// 		}
// 		i++;
// 	}
// }

void	treat_input(char **input)
{
	treat_space(*input);
	treat_quote(*input);
	// treat_dollar(*input);
}
