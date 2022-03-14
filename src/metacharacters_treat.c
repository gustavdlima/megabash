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

void	metacharacters_treat(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == 35 || cmd[i] == 35 || cmd[i] == 38 || cmd[i] == 40 || cmd[i] == 41)
		{
			// printf("Metacaracters")
		}
	}
}

