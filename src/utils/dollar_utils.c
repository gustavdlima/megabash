/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalves <gusalves@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 21:01:56 by gusalves          #+#    #+#             */
/*   Updated: 2022/07/15 21:01:56 by gusalves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_there_dollar(char *cmd)
{
	int	cmd_len;
	int	i;

	i = 0;
	cmd_len = ft_strlen(cmd);
	while (cmd[i] || i < cmd_len)
	{
		if (cmd[i] == '$')
			return (true);
		i++;
	}
	return (false);
}

int	wheres_dollar(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '$')
			return (i);
		i++;
	}
	return (i);
}

char	*interpret_dollar(char *cmd, int position)
{
	char	*interpreted;
	char	*name;
	t_env	*env_var;

	if (cmd[position + 1] == '{')
		position++;
	name = get_name(cmd + position + 1);
	env_var = get_env_node(g_megabash.env, name);
	if (env_var != NULL)
	{
		interpreted = ft_strdup(env_var->content);
		free (name);
		return (interpreted);
	}
	free (name);
	free_env(env_var);
	name = ft_strdup("");
	return (name);
}

int	single_dollar(char *cmd)
{
	int	i;

	i = 1;
	if (cmd[i] == '?' || cmd[i] == '{')
		return (false);
	if (cmd[i] == 1 || cmd[i] == ' ' || !cmd[i] || cmd[i] == '$')
		return (true);
	if (ft_isascii(cmd[i]) != 0 && ft_isalnum(cmd[i]) == 0)
		return (true);
	return (false);
}

int	is_question_mark(char *cmd)
{
	int	i;

	i = 1;
	if (cmd[i] == '?')
		return (true);
	return (false);
}
