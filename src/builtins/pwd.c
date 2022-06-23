#include "minishell.h"

void	pwd(char **matrix)
{
	char	*directory;
	t_env	*node;

	if (matrix[1])
	{
		error_message("megabash error: pwd: too many arguments", 1);
		exit(1);
	}
	directory = getcwd(NULL, 0);
	if (directory)
	{
		node = get_env_node(g_megabash.env, "PWD");
		ft_putendl_fd(node->content, 1);
	}
	free (directory);
	g_megabash.exit_status = 0;
	exit(0);
}
