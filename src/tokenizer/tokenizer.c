/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalves <gusalves@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 21:01:20 by gusalves          #+#    #+#             */
/*   Updated: 2022/07/15 21:01:20 by gusalves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	treat_token_list(void)
{
	t_token	*temp;

	temp = g_megabash.token_list;
	while (temp)
	{
		treat_quote(temp->content);
		if (is_there_dollar(temp->content) == true)
			temp->content = treat_dollar(temp->content);
		temp = temp->next;
	}
}

void	tokenizer(char *input)
{
	char	**temp;
	char	*new_token;
	int		i;

	i = 1;
	temp = ft_split(input, ' ');
	if (temp != NULL)
	{
		g_megabash.token_list = token_lst_new(temp[0]);
		while (temp[i])
		{
			new_token = ft_strdup(temp[i]);
			token_addback(&g_megabash.token_list, token_lst_new(new_token));
			free(new_token);
			if (temp[i])
				i++;
		}
	}
	free_matrix(temp);
	set_token_type(g_megabash.token_list);
}
