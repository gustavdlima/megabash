#include "minishell.h"

void	initialize_struct(t_root *root, char **envp)
{
	root->envp = envp;
	root->exit_status = 0;
}
