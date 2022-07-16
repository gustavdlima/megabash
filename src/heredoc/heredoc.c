/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalves <gusalves@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 20:56:01 by gusalves          #+#    #+#             */
/*   Updated: 2022/07/15 22:03:25 by gusalves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	save_data(char *content, int fd)
{
	char	*content_to_doc;

	content_to_doc = ft_strjoin(content, "\n");
	free(content);
	fd = open("./src/heredoc/heredoc_content", O_WRONLY | O_CREAT | O_APPEND,
			0777);
	if (!content_to_doc)
		write(fd, "", 1);
	else
		write(fd, content_to_doc, ft_strlen(content_to_doc));
	free(content_to_doc);
}

static void	prompt_loop(t_redirect *command_list, int fd)
{
	t_redirect	*temp;
	char		*read;

	temp = command_list;
	while (1)
	{
		read = readline("> ");
		if (!read)
		{
			free_env(g_megabash.env);
			g_megabash.exit_status = 0;
			free_commands(g_megabash.cmd_list);
			exit(g_megabash.exit_status);
		}
		if (read && !ft_new_strncmp(temp->content, read))
			save_data(read, fd);
		else if (ft_new_strncmp(temp->content, read))
		{
			g_megabash.exit_status = 0;
			fd = open("./src/heredoc/heredoc_content",
					O_WRONLY | O_CREAT | O_APPEND, 0777);
			break ;
		}
	}
}

int	heredoc(t_redirect *command_list, int **fd)
{
	pid_t	pid;
	int		heredoc_fd;

	heredoc_fd = 0;
	if (g_megabash.multiple_cmds == true)
		check_and_dup(g_megabash.stdin_backup, STDIN_FILENO);
	signal_handler_heredoc();
	pid = fork();
	if (pid == 0)
	{
		prompt_loop(command_list, heredoc_fd);
		free_commands(g_megabash.cmd_list);
		free_env(g_megabash.env);
		if (fd)
			free_int_matrix(fd);
		exit(0);
	}
	waitipid_save_exit_status(pid);
	heredoc_fd = open("./src/heredoc/heredoc_content", O_RDONLY, 0777);
	return (heredoc_fd);
}
