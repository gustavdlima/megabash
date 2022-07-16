/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_utils_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalves <gusalves@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 20:59:40 by gusalves          #+#    #+#             */
/*   Updated: 2022/07/15 20:59:41 by gusalves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	token_addback(t_token **lst, t_token *new)
{
	t_token	*last_node;

	if (*lst)
	{
		last_node = token_last_node(*lst);
		last_node->next = new;
		new->prev = last_node;
	}
	else
		*lst = new;
}

t_token	*token_last_node(t_token *lst)
{
	if (lst)
	{
		while (lst->next != NULL)
			lst = lst->next;
		return (lst);
	}
	return (NULL);
}

struct s_token	*get_token_node(t_token *list, char *name)
{
	while (list)
	{
		if (ft_new_strncmp(list->content, name) == true)
			return (list);
		list = list->next;
	}
	return (NULL);
}

t_token	*token_lst_new(char *content)
{
	t_token	*element;

	element = malloc(sizeof(t_token));
	if (element)
	{
		element->type = 0;
		element->content = ft_strdup(content);
		element->next = NULL;
		element->prev = NULL;
		return (element);
	}
	return (0);
}
