#include "minishell.h"

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

static int	return_different_redirection_signs(char sign)
{
	dprintf(2, "megabash: syntax error near unexpected token `%c'\n", sign);
	g_megabash.exit_status = 2;
	return (true);
}

int	different_redirection_signs(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '<')
		{
			i++;
			if (cmd[i] == '<')
				i++;
			if (cmd[i] == '>')
				return (return_different_redirection_signs(cmd[i]));
		}
		else if (cmd[i] == '>')
		{
			i++;
			if (cmd[i] == '>')
				i++;
			if (cmd[i] == '<')
				return (return_different_redirection_signs(cmd[i]));
		}
		if (cmd[i])
			i++;
	}
	return (false);
}

static int	is_valid_string(char *str)
{
	if (!str || (ft_new_strncmp("|", str)) || (ft_new_strncmp("||", str)
			|| (ft_new_strncmp("&", str)) || (ft_new_strncmp("&&", str))
			|| (ft_new_strncmp(">>", str)) || (ft_new_strncmp(">", str))
			|| (ft_new_strncmp("<<", str)) || (ft_new_strncmp("<", str))))
		return (false);
	return (true);
}

int	no_words_after_redirect(char *input)
{
	int	i;

	i = ft_strlen(input);
	if (i >= 1)
		i--;
	if (!is_valid_string(input + i))
	{
		dprintf (2, "megabash: syntax error near unexpected token `%s\'\n",
		input + i);
		g_megabash.exit_status = 2;
		return (true);
	}
	return (false);
}
