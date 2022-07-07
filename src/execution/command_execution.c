#include "minishell.h"

void	execute_command_and_redirection(t_commands *pivot, int execute)
{
	// t_redirect *temp = pivot->redirect;

	if (pivot->redirect)
		execute = redirect_commands(pivot);
	if (pivot->cmd && child_is_builtin(pivot->cmd) == true && execute == true)
		execute_builtin(pivot);
	else if (execute == true)
		execute_execve(pivot);
	// else
	// {
		free(g_megabash.last_input);
		free_commands(g_megabash.cmd_list);
		free_env(g_megabash.env);
		exit(g_megabash.exit_status);
	// }
}

void	execute_multiple_commands(void)
{
	int			**fd;
	int			i;

	g_megabash.multiple_cmds = true;
	fd = NULL;
	fd = malloc_int_matrix(fd);
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
		waitpid(-1, &g_megabash.exit_status, 0);
	free_int_matrix(fd);
}

void	execute_single_command(void)
{
	t_commands	*pivot;
	pid_t		pid;
	int			execute;

	execute = true;
	g_megabash.multiple_cmds = false;
	pivot = g_megabash.cmd_list;
	if (pivot->cmd && parent_is_builtin(pivot->cmd) == true)
	{
		execute_builtin(pivot);
		return ;
	}
	pid = fork();
	if (pid == 0)
		execute_command_and_redirection(pivot, execute);
	waitpid(pid, &g_megabash.exit_status, 0);
}
