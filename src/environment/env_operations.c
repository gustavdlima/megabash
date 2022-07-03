#include "minishell.h"

void	print_env(t_env *env)
{
	if (!env)
		return ;
	while (env)
	{
		printf("%s=", env->name);
		printf("%s\n", env->content);
		env = env->next;
	}
}

struct s_env	*get_env_node(t_env *list, char *name)
{
	t_env *list_temp;

	list_temp = list;
	while (list_temp)
	{
		if (ft_new_strncmp(list_temp->name, name) == true)
			return (list_temp);
		list_temp = list_temp->next;
	}
	return (NULL);
}

void	env_node_delete(t_env *list)
{
	t_env	*temp;

	temp = list;
	if (list)
	{
		if (list->next && !list->prev)
		{
			list = list->next;
			list->prev = NULL;
			g_megabash.env = list;
			free_unset(temp);
		}
		else if (list->next && list->prev)
		{
			list = temp->next;
			list->prev = temp->prev;
			list->prev->next = list;
			free_unset(temp);
		}
		else
		{
			list = temp->prev;
			list->next = NULL;
			free_unset(temp);
		}
	}
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
