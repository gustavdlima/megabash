#include "minishell.h"

// funcao para colocar o CONTENT como NULL
// funcao para excluir node com NAME especifico
// funcao para adicionar um addback com NAME e CONTENT

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

struct s_env 	*get_env_node(t_env *list, char *name, int size)
{
	while (list)
	{
		if (!ft_memcmp(list->name, name, size))
			return (list);
		// printf("Content = %s\n", list->name);
		list = list->next;
	}
	return NULL;
}

void	env_node_addback(t_env *list, char *name, char *content)
{
	env_addback(&list, env_lstnew(name, content));
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
