/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chdir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalves <gusalves@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 20:50:11 by gusalves          #+#    #+#             */
/*   Updated: 2022/07/15 20:50:16 by gusalves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	new_pwd_env(void)
{
	char	*directory;
	t_env	*env_node;
	t_env	*temp;

	temp = g_megabash.env;
	directory = getcwd(NULL, 0);
	env_node = get_env_node(temp, "PWD");
	if (env_node == NULL)
		env_addback(&g_megabash.env, env_lst_new("PWD", directory));
	else
	{
		free(env_node->content);
		env_node->content = ft_strdup(directory);
	}
	free(directory);
}

void	new_oldpwd_env(void)
{
	char	*directory;
	t_env	*env_node;
	t_env	*temp;

	temp = g_megabash.env;
	directory = getcwd(NULL, 0);
	env_node = get_env_node(temp, "OLDPWD");
	if (env_node == NULL)
		env_addback(&g_megabash.env, env_lst_new("OLDPWD", directory));
	else
	{
		free(env_node->content);
		env_node->content = ft_strdup(directory);
	}
	free(directory);
}
