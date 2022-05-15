#include "minishell.h"

static void	free_exit_builtin(char *string, char **matrix)
{
	free(string);
	free_matrix(matrix);
	free_env(g_megabash.env);
	rl_clear_history();
}

static void	print_error_exit(char *error_msg)
{
	g_megabash.exit_status = 1;
	ft_putstr_fd("megabash error: exit: ", 2);
	ft_putendl_fd(error_msg, 2);
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

void	exit_builtin(char **matrix)
{
	char **cmd;

	printf("exit\n");
	if (matrix)
	{
		cmd = ft_split(matrix, ' ');
		if (matrix_size(cmd) > 0)
		{
			print_error_exit("too many arguments");
			return ;
		}
		if (cmd[1] && !check_arg(cmd[1]))
			g_megabash.exit_status = ft_atoi(cmd[1]);
		if (cmd[1] && check_arg(cmd[1]))
			g_megabash.exit_status = 2;
		free_exit_builtin(matrix, cmd);
	}
	exit(g_megabash.exit_status);
}
