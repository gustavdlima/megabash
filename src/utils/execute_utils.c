#include "minishell.h"

void	execute_execve(t_commands *cmd_list)
{
	char	*pathway;

	pathway = what_cmd(cmd_list->cmd);
	if (!pathway)
		error_message("Command does not exists", 1);
	else
		execve(pathway, cmd_list->content, g_megabash.envp);
}

int	**malloc_int_matrix(void)
{
	int	**fd;
	int	i;

	if (g_megabash.pipe > 0)
		i = g_megabash.pipe;
	else
		i = 1;
	fd = (int **)malloc((i + 1) * sizeof(int *));
	while (i >= 0)
	{
		fd[i] = malloc(2 * sizeof(int));
		i--;
	}
	return (fd);
}
