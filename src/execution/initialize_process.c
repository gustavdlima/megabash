/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_process.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmilson- <jmilson-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 20:52:05 by gusalves          #+#    #+#             */
/*   Updated: 2022/07/16 22:21:39 by jmilson-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_heredoc_fd(t_commands *pivot, int **fd)
{
	t_redirect	*temp;
	int			heredoc_fd;

	heredoc_fd = -1;
	if (pivot->redirect)
	{
		temp = pivot->redirect;
		while (temp)
		{
			if (temp->type == is_here_doc)
			{
				g_megabash.stdin_backup = dup(STDIN_FILENO);
				heredoc_fd = heredoc(temp, fd);
			}
			temp = temp->next;
		}
	}
	return (heredoc_fd);
}

void	child_proccess(t_commands *pivot, int **fd, int i)
{
	int	heredoc_fd;

	if (i != 0)
	{
		close(fd[i - 1][1]);
		heredoc_fd = get_heredoc_fd(pivot, fd);
		if (heredoc_fd == -1)
			check_and_dup(fd[i - 1][0], STDIN_FILENO);
	}
	if (i == 0)
		heredoc_fd = get_heredoc_fd(pivot, fd);
	if (fd[i] != NULL)
	{
		close(fd[i][0]);
		check_and_dup(fd[i][1], STDOUT_FILENO);
	}
	free_int_matrix(fd);
	execute_command_and_redirection(pivot, heredoc_fd);
}

void	initialize_execution_process(int **fd)
{
	t_commands	*pivot;
	pid_t		pid;
	int			i;

	pivot = g_megabash.cmd_list;
	i = 0;
	while (pivot)
	{
		if (pivot->cmd && parent_is_builtin(pivot->cmd) == true)
		{
			execute_builtin(pivot);
			i++;
			pivot = pivot->next;
			continue ;
		}
		pid = fork();
		signal_handler_child();
		if (pid == 0)
			child_proccess(pivot, fd, i);
		if (fd[i])
			close(fd[i][1]);
		i++;
		pivot = pivot->next;
	}
}
