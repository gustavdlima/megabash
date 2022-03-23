#include "minishell.h"

void	print_env(t_env *env)
{
	if (!env)
		return ;
	while(env->next)
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
		if (!ft_memcmp(list->name, name, ft_strlen(name)))
			return (list);
		list = list->next;
	}
	return NULL;
}

void	env_node_delete(t_env *list, char *name)
{
	if (env_name_check(list, name) == 0)
	{
		while (list->next)
		{
			if (list->next->name == name)
			{
				list->next = list->next->next;
				break ;
			}
			list = list->next;
		}
	}
	return ;
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
