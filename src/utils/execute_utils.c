#include "minishell.h"

void	execute_execve(void)
{
	char	*pathway;

	pathway = what_cmd(g_megabash.cmd_list->cmd);
	if (!pathway)
		error_message("NÃO EXISTE!!", 1);
	execve(pathway, g_megabash.cmd_list->content, g_megabash.envp);
}

int **malloc_int_matrix()
{
	fd = (int **)ft_calloc(g_megabash.pipe, sizeof(int *));
	i = g_megabash.pipe - 1;
	while (i >= 0)
	{
		fd[i] = ft_calloc(2, sizeof(int));
		i--;
	}
}
