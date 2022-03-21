#include "minishell.h"

void	unset(t_root *root, t_env *env)
{
	int	i;

	i = 1;
	while (root->command[i])
	{
		env_node_delete(env, root->command[i]);
		i++;
	}
}

// remover o no
