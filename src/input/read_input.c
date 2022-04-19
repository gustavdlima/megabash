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
	free(g_megabash.last_input);
	g_megabash.last_input = ft_strdup(cmd);
	return (TRUE);
}

char	*read_input(void)
{
	char	*input;
	char	*temp;
	char	*aux;

	input = readline("\033[0;35mmegabash$ \033[0m");
	if (input)
	{
		while (open_quotes(input) == TRUE || pipe_no_arguments(input) == TRUE)
		{
			temp = readline("\033[0;35m> \033[0m");
			aux = ft_strjoin(input, temp);
			free(input);
			free(temp);
			input = ft_strjoin(aux, "\n");
			free(aux);
		}
	}
	if (!input || !ft_strncmp(input, "exit", 4))
		exit_builtin(input);
	if (input && is_it_history(input) == TRUE)
	{
		add_history(input);
	}
	return (input);
}
