#include "minishell.h"

int	env_name_check(t_env *lst, char *name)
{
	while (lst->next)
	{
		if (lst->name == name)
			return(1);
		lst = lst->next;
	}
	return (0);
}

int	env_lstsize(t_env *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

t_env	*env_lstnew(char *name, char *content)
{
	t_env	*element;

	element = malloc(sizeof(t_env));
	if (element)
	{
		element->name = name;
		element->content = content;
		element->next = NULL;
		return (element);
	}
	return (0);
}

void	env_addback(t_env **lst, t_env *new)
{
	t_env	*i;

	if (*lst)
	{
		i = env_last_node(*lst);
		i->next = new;
	}
	else
	{
		*lst = new;
	}
}

t_env	*env_last_node(t_env *lst)
{
	if (lst)
	{
		while (lst->next != NULL)
		{
			lst = lst->next;
		}
		return (lst);
	}
	return (0);
}
