#include "minishell.h"

t_global	g_megabash;

int	special_or_metacharacters(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == ';' || cmd[i] == 92 || cmd[i] == '(' || cmd[i] == ')'
			|| cmd[i] == '&' || cmd[i] == '#')
			return (TRUE);
		i++;
	}
	return (FALSE);
}

int	unquotted_command(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == 34 || cmd[i] == 39)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	open_quotes(char *cmd)
{
	int	i;
	int	sign;

	i = 0;
	sign = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\'' || cmd[i] == '\"')
		{
			sign = cmd[i];
			i++;
			while (cmd[i] && cmd[i] != sign)
			{
				i++;
			}
			if (cmd[i] != sign)
				return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

void	validate_input(char *input)
{
	//não é builtin
	if (open_quotes(input) == TRUE)
	{
		ft_putendl_fd("Open quotes.", 2);
		g_megabash.exit_status = 130;
		exit (130);
	}
	if (unquotted_command(input) == TRUE
		&& special_or_metacharacters(input) == TRUE)
	{
		ft_putendl_fd("Forbidden characters on unquotted command.", 2);
		g_megabash.exit_status = 1;
		exit (1);
	}
	// pipe sem argumento
	// erro de sintax
}

char	*read_input(void)
{
	char	*input;

	input = readline("minishell$ ");
	add_history(input);
	return (input);
}

void	megastart(void)
{
	char	*read;

	while (1)
	{
		read = read_input();
		validate_input(read);
	}
}

int	main(int argc, char **argv, char **envp)
{
	if (argc > 1 && argv != NULL)
	{
		ft_putendl_fd("Error: Try only ./minishell", 2);
		exit(1);
	}
	environment(envp);
	megastart();
	return (0);
}
