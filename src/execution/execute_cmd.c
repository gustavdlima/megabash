#include "minishell.h"

void	execute_command_and_redirection(t_commands *pivot, int execute)
{
	if (pivot->redirect)
		execute = redirect_commands(pivot);
	if (pivot->cmd && child_is_builtin(pivot->cmd) == true && execute == true)
	{
		execute_builtin(pivot);
	}
	else if (execute == true)
		execute_execve(pivot);
	else
		exit(g_megabash.exit_status);
}

void	child_proccess(t_commands *pivot, int **fd, int i)
{
	int	execute;

	execute = true;
	if (i != 0)
	{
		close(fd[i - 1][1]);
		check_and_dup(fd[i - 1][0], STDIN_FILENO);
	}
	if (fd[i] != NULL)
	{
		close(fd[i][0]);
		check_and_dup(fd[i][1], STDOUT_FILENO);
	}
	execute_command_and_redirection(pivot, execute);
}

void	initialize_process(int **fd)
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

void	execute_multiple_commands(void)
{
	int			**fd;
	int			i;

	fd = malloc_int_matrix();
	i = 0;
	while (fd[i])
	{
		if (pipe(fd[i]) == -1)
			error_message_exit("Proccess error : pipe", 1);
		i++;
	}
	initialize_process(fd);
	i = 0;
	while (i++ < g_megabash.pipe + 1)
		waitpid(-1, &g_megabash.exit_status, 0);
}

void	execute_single_command(void)
{
	t_commands	*pivot;
	pid_t		pid;
	int			execute;

	execute = true;
	pivot = g_megabash.cmd_list;
	if (pivot->cmd && parent_is_builtin(pivot->cmd) == true)
	{
		execute_builtin(pivot);
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		printf("executando um comando simples sem ser parent builtin\n");
		execute_command_and_redirection(pivot, execute);
	}
	waitpid(pid, &g_megabash.exit_status, 0);
}
