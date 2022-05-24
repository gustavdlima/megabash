#include "minishell.h"

void	execute_execve(t_commands *cmd_list)
{
	char	*pathway;

	pathway = what_cmd(cmd_list->cmd);
	if (!pathway)
		error_message("NÃO EXISTE!!", 1);
	execve(pathway, cmd_list->content, g_megabash.envp);
}

int	**malloc_int_matrix(void)
{
	int	**fd;
	int	i;

	i = g_megabash.pipe - 1;
	fd = (int **)ft_calloc(g_megabash.pipe, sizeof(int *));
	while (i >= 0)
	{
		fd[i] = ft_calloc(2, sizeof(int));
		i--;
	}
	return (fd);
}
