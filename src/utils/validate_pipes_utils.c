#include "minishell.h"

static	int	counting_args(char **arguments)
{
	int	i;
	int	args;

	i = 0;
	args = 0;
	while (arguments[i])
	{
		if (ft_new_strncmp(arguments[i], "\n") == false
			&& only_space(arguments[i]) == false)
			args++;
		i++;
	}
	return (args);
}

static int	counting_pipes(char *cmd)
{
	int	i;
	int	pipes;

	i = 0;
	pipes = 0;
	while (cmd[i])
	{
		if (cmd[i] == '|')
		{
			i++;
			pipes++;
		}
		if (cmd[i])
			i++;
	}
	return (pipes);
}

int	pipe_no_arguments(char *cmd)
{
	char	**arguments;
	int		pipes;
	int		args;

	treat_char(cmd, '|', 6);
	pipes = counting_pipes(cmd);
	if (pipes != 0)
	{
		arguments = ft_split(cmd, '|');
		args = counting_args(arguments);
		free_matrix(arguments);
		reverse_char(cmd, 6, '|');
		if (pipes == (args - 1) || cmd[0] == '|')
			return (false);
		return (true);
	}
	reverse_char(cmd, 6, '|');
	return (false);
}
