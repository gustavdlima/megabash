/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalves <gusalves@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 21:00:26 by gusalves          #+#    #+#             */
/*   Updated: 2022/07/15 21:00:29 by gusalves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cmd_operation(char *cmd_string, char *token_content)
{
	char	*temp;

	cmd_string = insert_caracter(cmd_string, ' ');
	temp = ft_strjoin(cmd_string, token_content);
	free(cmd_string);
	cmd_string = ft_strdup(temp);
	free(temp);
	return (cmd_string);
}

t_commands	*copy_string_to_inside_matrix(t_commands *cmd_list, char *string)
{
	int		i;
	char	*temp;
	char	*new_string;

	i = 0;
	new_string = ft_strdup("");
	while (cmd_list->content[i])
	{
		temp = ft_strjoin(new_string, cmd_list->content[i]);
		free(new_string);
		new_string = ft_strdup(temp);
		new_string = insert_caracter(new_string, ' ');
		free(temp);
		i++;
	}
	new_string = insert_caracter(new_string, ' ');
	temp = ft_strjoin(new_string, string);
	free_matrix(cmd_list->content);
	cmd_list->content = ft_split(temp, ' ');
	free(new_string);
	free(temp);
	return (cmd_list);
}
