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
			return (TRUE);
		i++;
	}
	if (ft_atoi(arg) > 0 && ft_atoi(arg) <= 255)
		return (FALSE);
	return (TRUE);
}

void	exit_builtin(char *arg)
{
	char **matrix;

	printf("exit\n");
	matrix = ft_split(arg, ' ');
	if (matrix_size(matrix) > 1)
	{
		print_error_exit("too many arguments");
		return ;
	}
	if (matrix[1] && !check_arg(matrix[1]))
		g_megabash.exit_status = ft_atoi(matrix[1]);
	if (matrix[1] && check_arg(matrix[1]))
		g_megabash.exit_status = 2;
	free_exit_builtin(arg, matrix);
	exit(g_megabash.exit_status);
}
