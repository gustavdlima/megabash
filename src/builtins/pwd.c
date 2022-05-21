#include "minishell.h"

void	pwd(char **matrix)
{
	char	*directory;
	t_env	*node;

	if (matrix[1])
	{
		ft_putendl_fd("megabash error: pwd: too many arguments", 2);
		return ;
	}
	directory = getcwd(NULL, 0);
	if (directory)
	{
		node = get_env_node(g_megabash.env, "PWD");
		ft_putendl_fd(node->content, 1);
	}
	free (directory);
}
