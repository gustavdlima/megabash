/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_list_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalves <gusalves@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 20:59:02 by gusalves          #+#    #+#             */
/*   Updated: 2022/07/15 20:59:02 by gusalves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect_addback(t_redirect **lst, t_redirect *new)
{
	t_redirect	*i;

	if (*lst)
	{
		i = redirect_last_node(*lst);
		i->next = new;
	}
	else
		*lst = new;
}

t_redirect	*redirect_last_node(t_redirect *lst)
{
	if (lst)
	{
		while (lst->next != NULL)
			lst = lst->next;
		return (lst);
	}
	return (NULL);
}

t_redirect	*redirect_lst_new(void)
{
	t_redirect	*element;

	element = malloc(sizeof(t_redirect));
	if (element)
	{
		element->type = 0;
		element->content = NULL;
		element->next = NULL;
		return (element);
	}
	return (0);
}

void	free_redirect(t_redirect *redirections)
{
	t_redirect	*temp;

	while (redirections)
	{
		temp = redirections;
		redirections = redirections->next;
		free(temp->content);
		free(temp);
	}
}

int	redirect_lst_size(t_redirect *lst)
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
