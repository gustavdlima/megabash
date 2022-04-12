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
			if (ft_new_strncmp(list->next->name, name) == TRUE)
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
	while (command[i])
	{
		printf("env name-> %s\n", command[i]);
		temp = get_env_previous_node(g_megabash.env, get_env_name(command[i]));
		printf("E LA VAMOS NOS\n");
		printf("--------------------------------------- %s\n", temp->name);
		if (temp)
		{
			env_node_delete(temp);
		}
		else
			return ;
		i++;
	}
}
