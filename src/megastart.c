#include "minishell.h"

void	megastart(void)
{
	pid_t	p_id;

	while (1)
	{
		command_line();
		p_id = fork();
		if (p_id == 0)
		{
			execute_process();
		}
		waitpid(p_id, NULL, WUNTRACED);
	}
	free(g_megabash.input);
	free_matrix(g_megabash.cmd->content);
}
