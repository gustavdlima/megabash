#include "minishell.h"

void	megastart(t_root *root)
{
	pid_t	child_pid;

	while(1)
	{
		command_line(root);
		root->command = space_treat(root->input);
		child_pid = fork();
		if (child_pid < 0)
			exit(1);
		if (child_pid == 0)
		{

		}
		else
		{
			waitpid(child_pid, NULL, WUNTRACED);
		}
		free(root->input);
		free_matrix(root->command);
	}
}
