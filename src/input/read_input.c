#include "minishell.h"

static int	theres_delimiter(char *cmd)
{
	int	i;
	int	delimiter;

	i = 0;
	delimiter = 0;
	while (cmd[i])
	{
		if (cmd[i] == '<')
			delimiter++;
		i++;
	}
	if (delimiter >= 2) //pode colocar mais delimitadores?
		return (TRUE);
	return (FALSE);
}

int	only_space(char *cmd)
{
	int	i;
	int	space;
	int	cmd_len;

	i = 0;
	space = 0;
	cmd_len = ft_strlen(cmd);
	while (cmd[i])
	{
		if (cmd[i] == ' ')
			space++;
		i++;
	}
	if (space == cmd_len)
		return (TRUE);
	return (FALSE);
}

static int	is_it_history(char *cmd)
{
	if (cmd == NULL)
		return (FALSE);
	if (only_space(cmd) == TRUE)
		return (FALSE);
	if (theres_delimiter(cmd) == TRUE)
		return (FALSE);
	if (ft_new_strncmp(cmd, g_megabash.last_input) == TRUE)
		return (FALSE);
	g_megabash.last_input = cmd;
	return (TRUE);
}

char	*read_input(void)
{
	char	*input;

	input = readline("megabash$ ");
	if (input == NULL)
	{
		free_megabash();
		exit (0);
	}
	if (!ft_strncmp(input, "exit", 4))
		exit_builtin(input);
	if (is_it_history(input) == TRUE)
	{
		add_history(input);
	}
	return (input);
}
