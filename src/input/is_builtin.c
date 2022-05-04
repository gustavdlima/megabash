#include "minishell.h"

int	is_builtin(char *input)
{
	if (ft_new_strncmp("export", input) == true)
		return (true);
	if (ft_new_strncmp("unset", input) == true)
		return (true);
	if (ft_new_strncmp("echo", input) == true)
		return (true);
	if (ft_new_strncmp("exit", input) == true)
		return (true);
	if (ft_new_strncmp("env", input) == true)
		return (true);
	if (ft_new_strncmp("pwd", input) == true)
		return (true);
	if (ft_new_strncmp("cd", input) == true)
		return (true);
	return (false);
}
