#include "minishell.h"

static int	return_different_redirection_signs(void)
{
	ft_putendl_fd("bash: syntax error near unexpected token of redirection", 2);
	g_megabash.exit_status = 2;
	return (TRUE);
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
				return (return_different_redirection_signs());
		}
		else if (cmd[i] == '>')
		{
			i++;
			if (cmd[i] == '>')
				i++;
			if (cmd[i] == '<')
				return (return_different_redirection_signs());
		}
		if (cmd[i])
			i++;
	}
	return (FALSE);
}

static int	no_arguments(char *cmd)
{
	if (ft_strlen(cmd) < 1)
		return (TRUE);
	if (only_space(cmd) == TRUE)
		return (TRUE);
	if (!cmd)
		return (TRUE);
	return(FALSE);
}

int	redirect_to_no_arguments(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '>' || cmd[i] == '<')
		{
			i++;
			if (cmd[i] == '>' || cmd[i] == '<')
				i++;
			if (no_arguments(cmd + i) == TRUE)
			{
				ft_putendl_fd("bash: syntax error near unexpected token `newline'", 2);
				g_megabash.exit_status = 2;
				return (TRUE);
			}
		}
		if (cmd[i])
			i++;
	}
	return (FALSE);
}

int	too_many_redirections(char *cmd)
{
	int	redirection;
	int	sign;
	int	i;

	i = 0;
	redirection = 1;
	while (cmd[i])
	{
		if (cmd[i] == '>' || cmd[i] == '<')
		{
			sign = cmd[i];
			while (cmd[++i] == sign)
				redirection++;
			if (redirection > 2)
			{
				printf("bash: syntax error near unexpected token `%c%c'\n", sign, sign);
				g_megabash.exit_status = 2;
				return (TRUE);
			}
			redirection = 0;
		}
		if (cmd[i])
			i++;
	}
	return (FALSE);
}
