#include "minishell.h"

void	execute_process(void)
{
	find_redirections();
	g_megabash.cmd_path = what_cmd(g_megabash.cmd->content[0]);
	if (g_megabash.cmd_path == NULL)
	{
		free_matrix(g_megabash.cmd->content);
		printf("Command not found.\n");
	}
	for (int j = 0; g_megabash.cmd->content[j]; j++)
		printf("Command:\t%s\n", g_megabash.cmd->content[j]);
	execve(g_megabash.cmd_path, g_megabash.cmd->content, g_megabash.envp);
}
