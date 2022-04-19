#include "minishell.h"

int	different_redirection_signs(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '<')
		{
			i++;
			if (cmd[i] == '>')
				return (TRUE);
		}
		else if (cmd[i] == '>')
		{
			i++;
			if (cmd[i] == '<')
				return (TRUE);
		}
		if (cmd[i])
			i++;
	}
	return (FALSE);
}
