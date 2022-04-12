#include "minishell.h"

int	env_name_check(t_env *lst, char *name)
{
	while (lst->next)
	{
		if (lst->name == name)
			return (TRUE);
		lst = lst->next;
	}
	return (FALSE);
}

int	env_lst_size(t_env *lst)
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

t_env	*env_lst_new(char *name, char *content)
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
		*lst = new;
}

t_env	*env_last_node(t_env *lst)
{
	if (lst)
	{
		while (lst->next != NULL)
			lst = lst->next;
		return (lst);
	}
	return (NULL);
}
