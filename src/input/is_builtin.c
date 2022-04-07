#include "minishell.h"

int is_builtin(char *input)
{
	if (ft_new_strncmp("export", input) == TRUE)
		return (TRUE);
	if (ft_new_strncmp("unset", input) == TRUE)
		return (TRUE);
	if (ft_new_strncmp("echo", input) == TRUE)
		return (TRUE);
	if (ft_new_strncmp("exit", input) == TRUE)
		return (TRUE);
	if (ft_new_strncmp("env", input) == TRUE)
		return (TRUE);
	if (ft_new_strncmp("pwd", input) == TRUE)
		return (TRUE);
	if (ft_new_strncmp("cd", input) == TRUE)
		return (TRUE);
	return (FALSE);
}
