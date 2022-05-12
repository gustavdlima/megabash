#include "minishell.h"

void	builtin_env(void)
{
	print_env(g_megabash.env);
}