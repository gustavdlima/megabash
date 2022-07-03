#include "minishell.h"

void	free_unset(t_env *list)
{
	free(list->name);
	free(list->content);
	free(list);
}

void	unset(char **command)
{
	t_env	*temp;
	t_env	*env_test;
	int		i;

	env_test = g_megabash.env;
	i = 1;
	if (command && !command[1])
		return ;
	while (command[i])
	{
		temp = get_env_node(env_test, command[i]);
		if (temp)
		{
			env_node_delete(temp);
		}
		i++;
	}
}
