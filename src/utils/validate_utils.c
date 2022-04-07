#include "minishell.h"

int	open_curly_bracket(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\'')
		{
			i++;
			while (cmd[i] && cmd[i] != '\'')
				i++;
			if (cmd[i] == '\'')
				i++;
		}
		if (cmd[i] == '$')
		{
			i++;
			if (cmd[i] == '{')
			{
				while (cmd[i] && cmd[i] != '}' && cmd[i] != '\"' && cmd[i] != '\'')
					i++;
				if (cmd[i] != '}')
					return (TRUE);
				if (!cmd[i])
					break ;
			}
		}
		if (cmd[i])
			i++;
	}
	return (FALSE);
}
