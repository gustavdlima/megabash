#include "minishell.h"

void	free_unset(t_env *list)
{
	free(list->name);
	free(list->content);
	free(list);
}

static t_env	*get_env_previous_node(t_env *list, char *name)
{
	while (list)
	{
		if (list->next)
		{
			if (ft_new_strncmp(list->next->name, name) == true)
				return (list);
		}
		list = list->next;
	}
	return (NULL);
}

void	unset(char **command)
{
	t_env *temp;
	int	i;

	i = 1;
	if (command && !command[1])
		return ;
	while (command[i])
	{
		temp = get_env_previous_node(g_megabash.env, command[i]);
		if (temp)
			env_node_delete(temp);
		else
			return ;
		i++;
	}
}
