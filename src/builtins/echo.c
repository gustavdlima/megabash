/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalves <gusalves@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 20:50:32 by gusalves          #+#    #+#             */
/*   Updated: 2022/07/15 20:50:35 by gusalves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	line_break_and_exit(int exit_status)
{
	ft_putstr_fd("\n", 1);
	free_commands(g_megabash.cmd_list);
	free_env(g_megabash.env);
	exit(exit_status);
}

void	echo(char **matrix)
{
	int		flag;
	int		i;

	flag = 0;
	i = 1;
	if (!matrix[1])
		line_break_and_exit(1);
	if (!ft_strncmp(matrix[1], "-n", 3))
	{
		flag = 1;
		i = 2;
	}
	while (matrix[i])
	{
		ft_putstr_fd(matrix[i], 1);
		if (matrix[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (flag == 0)
		line_break_and_exit(0);
	child_builtins_free_and_exit(0);
}
