/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalves <gusalves@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 20:53:30 by gusalves          #+#    #+#             */
/*   Updated: 2022/07/15 20:53:49 by gusalves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_builtins_free_and_exit(int exit_status)
{
	free_commands(g_megabash.cmd_list);
	free_env(g_megabash.env);
	exit(exit_status);
}

void	free_cmd_megabash(void)
{
	free_commands(g_megabash.cmd_list);
	free_env(g_megabash.env);
	rl_clear_history();
}

void	free_int_matrix(int **matrix)
{
	int	i;

	i = 0;
	if (matrix)
	{
		while (matrix[i])
		{
			free(matrix[i]);
			i++;
		}
		free(matrix);
	}
}

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	if (matrix)
	{
		while (matrix[i])
		{
			free(matrix[i]);
			i++;
		}
		free(matrix);
	}
}

void	free_env(t_env *env)
{
	t_env	*temp;

	while (env)
	{
		temp = env;
		env = env->next;
		free(temp->name);
		free(temp->content);
		free(temp);
	}
	free(env);
}
