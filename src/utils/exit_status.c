#include "minishell.h"

void	error_message(char *message, int exit_status)
{
	printf("%s\n", message);
	g_megabash.exit_status = exit_status;
}
