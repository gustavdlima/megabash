#include "minishell.h"

void	megastart(t_root *root)
{
	pid_t	p_id;
	while(1)
	{
		command_line(root);
		p_id = fork();
		if (p_id == 0)
		{
			execute_process(root);
		}
		waitpid(p_id, NULL, WUNTRACED);
	}
		free(root->input);
		free_matrix(root->command);
}
