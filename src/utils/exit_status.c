#include "minishell.h"

void	error_message(char *message, int exit_status)
{
	dprintf(2, "%s\n", message);
	g_megabash.exit_status = exit_status;
}

void	error_message_exit(char *message, int exit_status)
{
	dprintf(2, "%s\n", message);
	g_megabash.exit_status = exit_status;
	exit(exit_status);
}

void	update_exit_status_and_exit(int exit_status)
{
	g_megabash.exit_status = exit_status;
	free_commands(g_megabash.cmd_list);
	free_env(g_megabash.env);
	exit(exit_status);
}

void	quit_megabash(void)
{
	printf("exit\n");
	free_env(g_megabash.env);
	rl_clear_history();
	exit(g_megabash.exit_status);
}

void	waitipid_save_exit_status(int pid)
{
	waitpid(pid, &g_megabash.exit_status, 0);
	if (WIFEXITED(g_megabash.exit_status))
		g_megabash.exit_status = WEXITSTATUS(g_megabash.exit_status);
	else if (WIFSIGNALED(g_megabash.exit_status))
		g_megabash.exit_status = WTERMSIG(g_megabash.exit_status) + 128;
}
