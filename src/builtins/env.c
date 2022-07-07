#include "minishell.h"

static void	print_env_builtin(t_env *env)
{
	while (env)
	{
		ft_putstr_fd(env->name, 1);
		ft_putchar_fd('=', 1);
		ft_putendl_fd(env->content, 1);
		env = env->next;
	}
}

void	builtin_env(char **matrix)
{
	t_env	*temp;

	temp = g_megabash.env;
	if (matrix[1])
	{
		ft_putstr_fd("env: ‘", 2);
		ft_putstr_fd(matrix[1], 2);
		dprintf(2, "’: No such file or directory");
		update_exit_status_and_exit(1);
	}
	if (!get_env_node(temp, "PATH"))
	{
		ft_putstr_fd("megabash: env", 2);
		dprintf(2, ": No such file or directory");
		update_exit_status_and_exit(1);
	}
	if (matrix[0])
	{
		print_env_builtin(temp);
		g_megabash.exit_status = 0;
		child_builtins_free_and_exit(g_megabash.exit_status);
	}
}
