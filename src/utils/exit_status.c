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
	free_cmd_megabash();
	exit(exit_status);
}
