/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_token_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalves <gusalves@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 21:01:13 by gusalves          #+#    #+#             */
/*   Updated: 2022/07/15 21:01:14 by gusalves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_token_type(t_token *list)
{
	while (list)
	{
		if (!list->content)
			return ;
		if (check_operator(list->content[0]))
		{
			list->type = is_operator(list->content);
		}
		else
		{
			list->type = is_word;
		}
		list = list->next;
	}
}
