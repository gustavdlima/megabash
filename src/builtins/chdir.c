/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chdir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalves <gusalves@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 20:50:25 by gusalves          #+#    #+#             */
/*   Updated: 2022/07/15 20:50:27 by gusalves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	home_execute(void)
{
	t_env	*env_node;
	t_env	*temp;

	temp = g_megabash.env;
	env_node = get_env_node(temp, "HOME");
	if (env_node == NULL)
	{
		error_message("megabash: cd: HOME not set", 1);
	}
	else
	{
		new_oldpwd_env();
		chdir(env_node->content);
		new_pwd_env();
	}
}

static void	dash_execute(void)
{
	char	*directory;
	char	*new_dir;
	t_env	*env_node;
	t_env	*temp;

	temp = g_megabash.env;
	env_node = get_env_node(temp, "OLDPWD");
	if (env_node == NULL)
	{
		error_message("megabash: cd: OLDPWD not set", 1);
	}
	else
	{
		directory = ft_strdup(env_node->content);
		new_oldpwd_env();
		chdir(directory);
		new_dir = getcwd(NULL, 0);
		new_pwd_env();
		if (env_node->content)
			ft_putendl_fd(new_dir, 0);
		free(directory);
		free(new_dir);
	}
}

static void	expand_and_redirect(char *dir)
{
	char	*directory;
	t_env	*env_node;
	t_env	*temp;
	char	*sub_dir;

	sub_dir = ft_substr(dir, 2, ft_strlen(dir));
	temp = g_megabash.env;
	env_node = get_env_node(temp, "HOME");
	if (env_node == NULL)
		error_message("megabash: cd: HOME not set", 1);
	else
	{
		directory = ft_strdup(env_node->content);
		new_oldpwd_env();
		chdir(directory);
		new_pwd_env();
		free(directory);
	}
	if (chdir(sub_dir))
	{
		ft_putstr_fd("megabash: cd:", 2);
		ft_putstr_fd(sub_dir, 2);
		ft_putendl_fd(": No such file or directory", 2);
	}
	free(sub_dir);
}

void	cd(char **matrix)
{
	if (matrix_size(matrix) > 1)
		error_message("megabash: cd: too many arguments", 1);
	if (matrix_size(matrix) == 0
		|| !ft_strncmp(g_megabash.cmd_list->content[1], "~", 2))
		home_execute();
	else if (!ft_strncmp(g_megabash.cmd_list->content[1], "-", 2))
		dash_execute();
	else
	{
		new_oldpwd_env();
		if (chdir(matrix[1]) && matrix[1][0] != '~')
		{
			ft_putstr_fd("megabash: cd:", 2);
			ft_putstr_fd(matrix[1], 2);
			error_message(": No such file or directory", 1);
		}
		else if (matrix[1][0] == '~')
		{
			expand_and_redirect(matrix[1]);
		}
		new_pwd_env();
	}
}
