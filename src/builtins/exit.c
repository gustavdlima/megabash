#include "minishell.h"

int	is_numeric(char *string)
{
	int	i;

	i = 0;
	while (string[i])
	{
		if (!ft_isdigit(string[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	free_exit_builtin(void)
{
	free_megabash();
	rl_clear_history();
}

static int	check_arg(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (true);
		i++;
	}
	if (ft_atoi(arg) > 0 && ft_atoi(arg) <= 255)
		return (false);
	return (true);
}

void	exit_the_program(char **matrix)
{
	int		to_exit;

	to_exit = true;
	if (matrix)
	{
		if (matrix[1] && is_numeric(matrix[1]))
		{
			if (matrix[1] && !check_arg(matrix[1]))
				g_megabash.exit_status = ft_atoi(matrix[1]);
		}
		else if (matrix[1])
		{
			error_message("megabash error: exit: too many arguments", 1);
			to_exit = false;
		}
		else
			free_exit_builtin();
	}
	if (to_exit == true)
	{
		printf("exit\n");
		quit_megabash();
	}
}

void	b_exit(char **matrix)
{
	dprintf(2, "b_exit\n");
	if (matrix)
	{
		if (matrix[1] && is_numeric(matrix[1]))
		{
			if (matrix[1] && !check_arg(matrix[1]))
				g_megabash.exit_status = ft_atoi(matrix[1]);
		}
		else if (matrix[1])
			error_message("megabash error: exit: too many arguments", 1);
	}
	exit(g_megabash.exit_status);
}
