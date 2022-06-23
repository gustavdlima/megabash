#include "minishell.h"

void	builtin_env(char **matrix)
{
	t_env	*temp;

	temp = g_megabash.env;
	if (matrix[1])
	{
		ft_putstr_fd("env: ‘", 2);
		ft_putstr_fd(matrix[1], 2);
		error_message("’: No such file or directory", 1);
		exit(1);
	}
	else if (!get_env_node(g_megabash.env, "PATH"))
	{
		ft_putstr_fd("megabash: env", 2);
		error_message(": No such file or directory", 1);
		exit(1);
	}
	else
	{
		while(temp)
		{
			ft_putstr_fd(temp->name, 2);
			ft_putchar_fd('=', 1);
			ft_putendl_fd(temp->content, 1);
			temp = temp->next;
		}
		g_megabash.exit_status = 0;
		exit(0);
	}
}
