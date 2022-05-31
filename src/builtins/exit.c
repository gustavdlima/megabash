#include "minishell.h"


static int is_numeric(char *string)
{
	int	i;

	i = 0;
	while (string[i])
	{
		if(!ft_isdigit(string[i]))
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

void	b_exit(char **matrix)
{
	printf("exit\n");
	if (matrix)
	{
		if (matrix[1] && matrix[2])
		{
			ft_putendl_fd("megabash error: exit: too many arguments", 2);
			return ;
		}
		if (matrix[1] && is_numeric(matrix[1]))
		{
			if (matrix[1] && !check_arg(matrix[1]))
				g_megabash.exit_status = ft_atoi(matrix[1]);
		}
		if (matrix[1] && check_arg(matrix[1]))
				g_megabash.exit_status = 2;
		free_exit_builtin();
	}
	exit(g_megabash.exit_status);
}
