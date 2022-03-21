#include "minishell.h"

void	execute_process(t_root *root, t_env *env)
{
	find_redirections(root);
	if (check_builtins(root, env))
		printf("builtin checkado\n+");
	root->cmd_path = what_cmd(root->command[0], env);
	if (root->cmd_path == NULL)
	{
		free_matrix(root->command);
		printf("Command not found.\n");
	}
	for (int j = 0; root->command[j]; j++)
		printf("Command:\t%s\n", root->command[j]);
	execve(root->cmd_path, root->command, root->envp);
}
