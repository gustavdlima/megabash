#include "minishell.h"

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
		while (temp)
		{
			ft_putstr_fd(temp->name, 1);
			ft_putchar_fd('=', 1);
			ft_putendl_fd(temp->content, 1);
			temp = temp->next;
		}
		update_exit_status_and_exit(0);
	}
}
