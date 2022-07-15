#include "minishell.h"

void	execute_command_and_redirection(t_commands *pivot, int heredoc_fd)
{
	t_redirect	*temp;
	int			execute;

	temp = pivot->redirect;
	execute = true;
	if (pivot->redirect)
		execute = redirect_commands(temp, heredoc_fd);
	if (pivot->cmd && child_is_builtin(pivot->cmd) == true && execute == true)
		execute_builtin(pivot);
	else if (pivot->cmd && execute == true)
		execute_execve(pivot);
	free(g_megabash.last_input);
	free_commands(g_megabash.cmd_list);
	free_env(g_megabash.env);
	exit(g_megabash.exit_status);
}

void	execute_multiple_commands(void)
{
	int			**fd;
	int			i;

	g_megabash.multiple_cmds = true;
	fd = NULL;
	fd = malloc_int_matrix(fd);
	g_megabash.fd = fd;
	i = 0;
	while (fd[i])
	{
		if (pipe(fd[i]) == -1)
			error_message_exit("Proccess error : pipe", 1);
		i++;
	}
	initialize_execution_process(fd);
	i = 0;
	while (i++ < g_megabash.pipe + 1)
		waitipid_save_exit_status(-1);
	free_int_matrix(fd);
}

void	execute_single_command(void)
{
	t_commands	*pivot;
	pid_t		pid;

	g_megabash.multiple_cmds = false;
	pivot = g_megabash.cmd_list;
	if (pivot->cmd && parent_is_builtin(pivot->cmd) == true)
	{
		execute_builtin(pivot);
		return ;
	}
	pid = fork();
	if (pid == 0)
		execute_command_and_redirection(pivot, -42);
	waitipid_save_exit_status(pid);
}
