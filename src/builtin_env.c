#include "minishell.h"

void	env_b(t_root *root, t_env *env)
{
	(void)root;
	print_env(env);
	exit(2);
}
