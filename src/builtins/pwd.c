#include "minishell.h"

void	pwd(char **matrix)
{
	char	*directory;
	t_env	*node;
	t_env	*temp;

	temp = g_megabash.env;
	if (matrix[1])
	{
		dprintf(1, "megabash error: pwd: too many arguments");
		update_exit_status_and_exit(1);
	}
	directory = getcwd(NULL, 0);
	if (directory)
	{
		node = get_env_node(temp, "PWD");
		ft_putendl_fd(node->content, 1);
	}
	free (directory);
	free(g_megabash.last_input);
	free_commands(g_megabash.cmd_list);
	free_env(temp);
	exit(0);
}
