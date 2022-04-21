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

static int	is_valid_input(char *cmd)
{
	char	*str;
	int		i;

	i = 0;
	// if (cmd[0] == '|')
	// {
	// 	ft_putendl_fd("bash: syntax error near unexpected token `|'", 2);
	// 	g_megabash.exit_status = 42;
	// 	return (FALSE);
	// }
	while (cmd[i])
	{
		if (cmd[i] == '|')
			break ;
		i++;
	}
	str = ft_substr(cmd, 0, i);
	if (only_space(str) == TRUE || !str)
	{
		free(str);
		return (FALSE);
	}
	// str = ft_substr(cmd + i, 1, ft_strlen(cmd + i) - 1);
	// if (only_space(str) == TRUE)
	// 	return (FALSE);
	return (TRUE);
}

int	too_many_pipes(char *cmd)
{
	int	i;
	int	sign;

	i = 0;
	if (open_quotes(cmd) == TRUE)
		return (FALSE);
	treat_char(cmd, '|', 6);
	while (cmd[i])
	{
		if (cmd[i] == '|')
		{
			i++;
			while(cmd[i] == ' ')
				i++;
			if (cmd[i] == '|')
			{
				ft_putendl_fd("bash: syntax error near unexpected token `|'", 2);
				g_megabash.exit_status = 42;
				return (TRUE);
			}
		}
		if (cmd[i])
			i++;
	}
	reverse_char(cmd, 6, '|');
	return (FALSE);
}

char	*read_input(void)
{
	char	*input;
	char	*temp;
	char	*aux;

	input = readline("\033[0;35mmegabash$ \033[0m");
	if (open_quotes(input) == TRUE || pipe_no_arguments(input) == TRUE)
	{
		while (too_many_pipes(input) == FALSE)
		{
			temp = readline("\033[0;35m> \033[0m");
			aux = ft_strjoin(input, " ");
			free(input);
			if (temp && only_space(temp) == FALSE)
				input = ft_strjoin(aux, temp);
			else
				input = ft_strdup(aux);
			// free(temp);
			free(aux);
			if (open_quotes(input) == FALSE && pipe_no_arguments(input) == FALSE)
				break ;
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
