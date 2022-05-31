#include "minishell.h"

void	print_env(t_env *env)
{
	if (!env)
		return ;
	while(env)
	{
		printf("%s=", env->name);
		printf("%s\n", env->content);
		env = env->next;
	}
}

struct s_env 	*get_env_node(t_env *list, char *name)
{
	while (list)
	{
		if (ft_new_strncmp(list->name, name) == true)
			return (list);
		list = list->next;
	}
	return (NULL);
}

void	env_node_delete(t_env *list)
{
	t_env *temp;

	if (list->next)
	{
		if (list->next->next)
		{
			temp = list->next;
			list->next = list->next->next;
			free_unset(temp);
		}
		else
			list->next = NULL;
	}
	else
		list->next = NULL;
}

void	env_content_to_null(t_env *list, char *name)
{
	int	i;

	i = 0;
	while (list->next)
	{
		if (list->name == name)
			list->content = NULL;
		list = list->next;
		i++;
	}
}
