#include "minishell.h"

void	execute_process(t_root *root)
{
	int	cmd_size;
	int	i;

	i = 0;
	cmd_size = ft_strlen(root->input);
	root->command = matrix_split(root->input, cmd_size);
	while(root->command[i])
	{
		root->command[i] = no_quotes(root->command[i]);
		i++;
	}
	root->cmd_path = what_cmd(root->command[0]);
	if (root->cmd_path == NULL)
	{
		free_matrix(root->command);
		printf("Command not found.\n");
	}
	for (int j = 0; root->command[j]; j++)
		printf("Command:\t%s\n", root->command[j]);
	execve(root->cmd_path, root->command, root->envp);
}
