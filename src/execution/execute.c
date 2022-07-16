/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalves <gusalves@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 20:51:59 by gusalves          #+#    #+#             */
/*   Updated: 2022/07/15 20:52:00 by gusalves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	destroy_heredocs_fd(void)
{
	t_commands	*pivot;

	pivot = g_megabash.cmd_list;
	while (pivot)
	{
		if (pivot->redirect && pivot->redirect->type == is_here_doc)
			unlink("./src/heredoc/heredoc_content");
		pivot = pivot->next;
	}
}

void	executing_processes(void)
{
	if (g_megabash.pipe == 0)
		execute_single_command();
	else
		execute_multiple_commands();
	destroy_heredocs_fd();
}
