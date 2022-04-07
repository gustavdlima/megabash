#include "minishell.h"

int is_builtin(char *input)
{
	if (!strncmp(input, "export", 7))
		return (TRUE);
	if (!strncmp(input, "unset", 6))
		return (TRUE);
	if (!strncmp(input, "echo", 5))
		return (TRUE);
	if (!strncmp(input, "exit", 5))
		return (TRUE);
	if (!strncmp(input, "env", 4))
		return (TRUE);
	if (!strncmp(input, "pwd", 4))
		return (TRUE);
	if (!strncmp(input, "cd", 3))
		return (TRUE);
	return (FALSE);
}
