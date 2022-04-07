#include "minishell.h"

int	jump_special_or_metacharacters(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == ';' || cmd[i] == 92 || cmd[i] == '(' || cmd[i] == ')'
			|| cmd[i] == '&' || cmd[i] == '#' || cmd[i] == '[' || cmd[i] == ']')
			break ;
		i++;
	}
	return (i);
}

int	special_or_metacharacters(char c)
{
	if (c == ';' || c == '\\' || c == '(' || c == ')' || c == '&' || c == '#'
		|| c == '[' || c == ']')
		return (TRUE);
	return (FALSE);
}

int	pipe_no_arguments(char *cmd)
{
	char	**arguments;
	int		pipes;
	int		i;

	i = 0;
	pipes = 0;
	while (cmd[i])
	{
		if (cmd[i] == '|')
			pipes++;
		i++;
	}
	if (pipes != 0)
	{
		i = 0;
		arguments = ft_split(cmd, '|');
		while (arguments[i])
			i++;
		free_matrix(arguments);
		if (pipes == (i - 1))
			return (FALSE);
		return (TRUE);
	}
	return (FALSE);
}

int	wheres_special_metacharacter(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == ';' || cmd[i] == '\\' || cmd[i] == '(' || cmd[i] == ')'
			|| cmd[i] == '&' || cmd[i] == '#' || cmd[i] == '[' || cmd[i] == ']')
			return (i);
		i++;
	}
	return (i);
}

int	unquotted_special_metacharacters(char *cmd)
{
	int		i;
	int		sign;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\'' || cmd[i] == '\"')
		{
			sign = cmd[i];
			i++;
			while (cmd[i] != sign)
				i++;
		}
		if (special_or_metacharacters(cmd[i]) == TRUE)
			return (TRUE);
		i++;
	}
	return (FALSE);
}
