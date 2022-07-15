#include "minishell.h"

void	child_proccess(t_commands *pivot, int **fd, int i)
{
	t_redirect	*temp;
	int	heredoc_fd;

	heredoc_fd = -1;
	if (pivot->redirect)
	{
		temp = pivot->redirect;
		while (temp)
		{
			if (temp->type == is_here_doc)
			{
				g_megabash.stdin_backup = dup(STDIN_FILENO);
				heredoc_fd = heredoc(temp);
			}
			temp = temp->next;
		}
	}
	if (i != 0)
	{
		close(fd[i - 1][1]);
		if (heredoc_fd == -1)
			check_and_dup(fd[i - 1][0], STDIN_FILENO);
	}
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
		if (pid == 0)
			child_proccess(pivot, fd, i);
		if (fd[i])
			close(fd[i][1]);
		i++;
		pivot = pivot->next;
	}
}
