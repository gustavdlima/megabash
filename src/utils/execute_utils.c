#include "minishell.h"

void	execute_execve(t_commands *cmd_list)
{
	char	*pathway;

	if (!cmd_list->cmd)
		update_exit_status_and_exit(0);
	pathway = what_cmd(cmd_list->cmd);
	if (!pathway)
	{
		free(pathway);
		dprintf(2, "%s: ", cmd_list->cmd);
		error_message("command not found", 1);
		// free_cmd_megabash();
		update_exit_status_and_exit(1);
	}
	else
		execve(pathway, cmd_list->content, g_megabash.envp);
}

int	**malloc_int_matrix(int **fd)
{
	int	i;

	i = g_megabash.pipe;
	fd = (int **)malloc((i + 1) * sizeof(int *));
	fd[i] = NULL;
	i--;
	while (i >= 0)
	{
		fd[i] = malloc(2 * sizeof(int));
		i--;
	}
	return (fd);
}

int	check_and_dup(int old, int new)
{
	if (dup2(old, new) == -1)
	{
		error_message("Permission denined or FD does not exists.\n", 1);
		return (false);
	}
	else
		close(old);
	return (true);
}
