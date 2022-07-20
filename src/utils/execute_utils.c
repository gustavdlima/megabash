/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmilson- <jmilson-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 21:02:00 by gusalves          #+#    #+#             */
/*   Updated: 2022/07/19 23:57:07 by jmilson-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_executable(char *path)
{
	struct stat	buffer;

	if (path)
	{
		if (stat(path, &buffer) != 0)
			return (false);
		if ((buffer.st_mode & S_IFMT) == S_IFDIR)
			return (false);
		if ((buffer.st_mode & S_IXUSR))
			return (true);
	}
	return (false);
}

void	execute_execve(t_commands *cmd_list)
{
	char	*pathway;

	pathway = NULL;
	if (!cmd_list->cmd)
		update_exit_status_and_exit(217);
	if (ft_new_strncmp("/n", cmd_list->cmd))
		update_exit_status_and_exit(0);
	if (!only_quotes(cmd_list->cmd))
		pathway = what_cmd(cmd_list->content[0]);
	if (is_executable(pathway))
		execve(pathway, cmd_list->content, g_megabash.envp);
	else
	{
		if (cmd_list->content[0])
			dprintf(2, "%s: ", cmd_list->content[0]);
		if (pathway)
			free(pathway);
		error_message("command not found", 127);
		free_env(g_megabash.env);
		if (g_megabash.cmd_list)
			free_commands(g_megabash.cmd_list);
		exit(g_megabash.exit_status);
	}
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
		error_message("megabash: No such file or directory", 1);
		return (false);
	}
	else
		close(old);
	return (true);
}
