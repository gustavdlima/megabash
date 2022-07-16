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
					return (true);
				if (!cmd[i])
					break ;
			}
		}
		if (cmd[i])
			i++;
	}
	return (false);
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
				return (true);
		}
		i++;
	}
	return (false);
}

int	bash_syntax_error(char *cmd)
{
	if (cmd[0] == '|' || cmd[0] == ';' || cmd[0] == '&')
	{
		dprintf(2, "bash: syntax error near unexpected token `%c'\n", cmd[0]);
		g_megabash.exit_status = 2;
		return (true);
	}
	return (false);
}

int	pipe_no_arguments(char *cmd)
{
	int		i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '|')
		{
			i++;
			if (cmd[i])
			{
				if (only_space(cmd + i))
				{
					error_message
					("magabash: syntax error near unexpected token `|'\n", 2);
					return (true);
				}
			}
		}
		i++;
	}
	return (false);
}
