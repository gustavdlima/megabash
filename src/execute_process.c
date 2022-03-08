#include "minishell.h"

void	execute_process(t_root *root)
{
	int	cmd_size;

	cmd_size = ft_strlen(root->input);
	root->command = matrix_split(root->input, cmd_size);
	root->cmd_path = what_cmd(root->command[0]);
	if (root->cmd_path == NULL)
	{
		free_matrix(root->command);
		printf("Command not found.\n");
	}
	for (int i = 0; root->command[i]; i++)
		printf("Command:\t%s\n", root->command[i]);
	execve(root->cmd_path, root->command, root->envp);
}
