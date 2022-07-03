#include "minishell.h"

void	pwd(char **matrix)
{
	char	*directory;
	t_env	*node;

	if (matrix[1])
	{
		dprintf(1, "megabash error: pwd: too many arguments");
		update_exit_status_and_exit(1);
	}
	directory = getcwd(NULL, 0);
	if (directory)
	{
		node = get_env_node(g_megabash.env, "PWD");
		ft_putendl_fd(node->content, 1);
	}
	free (directory);
	update_exit_status_and_exit(0);
}
