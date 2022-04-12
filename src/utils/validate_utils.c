#include "minishell.h"

static int	incrementing_i_for_single_quotes(char *cmd)
{
	int	i;

	i = 0;
	if (cmd[i] == '\'')
	{
		i++;
		while (cmd[i] && cmd[i] != '\'')
			i++;
		if (cmd[i] == '\'')
			i++;
	}
	return (i);
}

int	open_curly_bracket(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		i = i + incrementing_i_for_single_quotes(cmd + i);
		if (cmd[i] == '$')
		{
			i++;
			if (cmd[i] == '{')
			{
				while (cmd[i] && cmd[i] != '}' && cmd[i] != '\"'
					&& cmd[i] != '\'')
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

int	open_quotes(char *cmd)
{
	int	sign;
	int	i;

	i = 0;
	sign = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\'' || cmd[i] == '\"')
		{
			sign = cmd[i];
			i++;
			while (cmd[i] && cmd[i] != sign)
				i++;
			if (cmd[i] != sign)
				return (TRUE);
		}
		i++;
	}
	return (FALSE);
}
