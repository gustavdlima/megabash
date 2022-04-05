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

int	special_or_metacharacters(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == ';' || cmd[i] == '\\' || cmd[i] == '(' || cmd[i] == ')'
			|| cmd[i] == '&' || cmd[i] == '#' || cmd[i] == '[' || cmd[i] == ']')
			return (TRUE);
		i++;
	}
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
	int		len;
	char	*aux;
	char	**input;

	i = 0;
	if ((ft_strnstr(cmd, "\'", ft_strlen(cmd)) == NULL || ft_strnstr(cmd, "\"", ft_strlen(cmd)) == NULL) && special_or_metacharacters(cmd) == TRUE)
		return (TRUE);
	if (special_or_metacharacters(cmd) == TRUE)
	{
		aux = cmd;
		treat_space(aux);
		input = ft_split(aux, ' ');
		while (input[i])
		{
			len = ft_strlen(input[i]) - 1;
			if ((input[i][0] != '\'' || input[i][0] != '\"')
				&& (input[i][len] != '\'' || input[i][len] != '\"')
				&& special_or_metacharacters(cmd) == TRUE)
				return (TRUE);
			i++;
		}
	}
	return (FALSE);
}
