/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalves <gusalves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 20:51:01 by gusalves          #+#    #+#             */
/*   Updated: 2022/07/17 22:57:58 by gusalves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	pwd_builtin_free_and_exit(char *directory, t_env *temp)
{
	free (directory);
	free_commands(g_megabash.cmd_list);
	free_env(temp);
	exit(0);
}

void	pwd(char **matrix)
{
	char	*directory;
	t_env	*node;
	t_env	*temp;

	temp = g_megabash.env;
	if (matrix[1])
		g_megabash.exit_status = 0;
	directory = getcwd(NULL, 0);
	if (directory)
	{
		node = get_env_node(temp, "PWD");
		if (!node)
		{
			error_message("megabash: pwd: PWD not set", 1);
			pwd_builtin_free_and_exit(directory, temp);
		}
		ft_putendl_fd(node->content, 1);
	}
	pwd_builtin_free_and_exit(directory, temp);
}
