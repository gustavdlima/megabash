#include "minishell.h"

void	builtin_env(char **matrix)
{
	print_env(g_megabash.env);
}