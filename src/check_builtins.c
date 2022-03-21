#include "minishell.h"

int	check_builtins(t_root *root, t_env *env)
{
	if (!ft_memcmp(root->command[0], "echo", 5))
		return (1);
	if (!ft_memcmp(root->command[0], "export", 7))
	{
		export(root, env);
		return (2);
	}
	if (!ft_memcmp(root->command[0], "unset", 6))
	{
		unset(root, env);
		return (3);
	}
	if (!ft_memcmp(root->command[0], "env", 4))
	{
		env_b(root, env);
		return (3);
	}
	return (0);
}
