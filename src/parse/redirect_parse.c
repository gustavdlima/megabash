/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_parse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalves <gusalves@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 21:00:36 by gusalves          #+#    #+#             */
/*   Updated: 2022/07/16 00:44:25 by gusalves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_type(char *content)
{
	if (!ft_strncmp(content, ">", 2))
		return (is_output);
	else if (!ft_strncmp(content, "<", 2))
		return (is_input);
	else if (!ft_strncmp(content, ">>", 3))
		return (is_append);
	else if (!ft_strncmp(content, "<<", 3))
		return (is_here_doc);
	else
		return (false);
}

t_token	*redirect_parse(t_token *token, t_redirect *redirect)
{
	char	*temp;

	redirect->type = redirect_type(token->content);
	token = token->next;
	redirect->content = ft_strdup("");
	while (token)
	{
		if (token->type == is_pipe)
			return (token);
		if (token->type == is_word && token->prev->type == is_word)
			return (token);
		if (token->type == is_word)
		{
			temp = ft_strjoin(redirect->content, token->content);
			free(redirect->content);
			redirect->content = ft_strdup(temp);
			free(temp);
		}
		if (token->type == is_redirect)
			return (token);
		token = token->next;
	}
	return (token);
}
