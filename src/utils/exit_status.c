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
	free(g_megabash.last_input);
	free_commands(g_megabash.cmd_list);
	// free_env(g_megabash.env);
	exit(exit_status);
}

void	quit_megabash(void)
{
	// //funcoes para dar free
	// free_env(g_megabash.env);
	free(g_megabash.last_input);
	if (g_megabash.cmd_list->content[1])
		free_commands(g_megabash.cmd_list);
	// free_token(g_megabash.token_list);
	free_env(g_megabash.env);
	rl_clear_history();
	exit(g_megabash.exit_status);
}
