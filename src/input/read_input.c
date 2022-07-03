#include "minishell.h"

// static int	theres_delimiter(char *cmd)
// {
// 	int	i;
// 	int	delimiter;

// 	i = 0;
// 	delimiter = 0;
// 	while (cmd[i])
// 	{
// 		if (cmd[i] == '<')
// 			delimiter++;
// 		i++;
// 	}
// 	if (delimiter >= 2) //pode colocar mais delimitadores?
// 		return (true);
// 	return (false);
// }
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
		if (cmd[i] == '\v' || cmd[i] == '\t'
			|| cmd[i] == '\r' || cmd [i] == ' ')
			space++;
		i++;
	}
	if (space == cmd_len)
		return (true);
	return (false);
}

static int	is_it_history(char *cmd)
{
	if (cmd == NULL)
		return (false);
	if (only_space(cmd) == true)
		return (false);
	// if (theres_delimiter(cmd) == true)
	// 	return (false);
	if (g_megabash.last_input)
	{
		if (ft_new_strncmp(cmd, g_megabash.last_input) == true)
			return (false);
		else
		{
			free(g_megabash.last_input);
			g_megabash.last_input = cmd;
		}
	}
	else
		g_megabash.last_input = cmd;
	return (true);
}

int	too_many_pipes(char *cmd)
{
	int	i;

	i = 0;
	if (open_quotes(cmd) == true)
		return (false);
	treat_char(cmd, '|', 6);
	while (cmd[i])
	{
		if (cmd[i] == '|')
		{
			i++;
			while (cmd[i] == ' ')
				i++;
			if (cmd[i] == '|')
			{
				error_message("bash: syntax error near unexpected token `|'",
					2);
				return (true);
			}
		}
		if (cmd[i])
			i++;
	}
	reverse_char(cmd, 6, '|');
	return (false);
}

void	complete_input_properly(char **input)
{
	char	*temp;
	char	*aux;

	if (open_quotes(*input) == true || pipe_no_arguments(*input) == true)
	{
		while (too_many_pipes(*input) == false)
		{
			temp = readline("\033[0;35m> \033[0m");
			aux = ft_strjoin(*input, " ");
			free(*input);
			if (temp && only_space(temp) == false)
				*input = ft_strjoin(aux, temp);
			else
				*input = ft_strdup(aux);
			free(temp);
			free(aux);
			if (open_quotes(*input) == false
				&& pipe_no_arguments(*input) == false)
				break ;
		}
	}
}

char	*read_input(void)
{
	char	*input;

	input = readline("\033[0;35mmegabash$ \033[0m");
	if (input)
	{
		complete_input_properly(&input);
		if (input && is_it_history(input) == true)
			add_history(input);
		return (input);
	}
	else
		exit (0);
}
