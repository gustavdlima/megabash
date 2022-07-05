#include "minishell.h"

static void	save_data(char *content, int fd)
{
	fd = open("./src/heredoc/heredoc_content", O_WRONLY | O_CREAT | O_TRUNC,
			0777);
	if (!content)
		write(fd, "", 1);
	else
		write(fd, content, ft_strlen(content));
}

static void	prompt_loop(t_commands *command_list, char *read, char *arraydoc, int fd)
{
	t_redirect *temp;

	temp = command_list->redirect;
	while (1)
	{
		signal_handler_heredoc(true);
		read = readline("> ");
		if (read || ft_new_strncmp(temp->content, read))
		{
			if (temp->type == is_here_doc)
			{
				if (!ft_strncmp(temp->content, read, ft_strlen(read)))
				{
					save_data(arraydoc, fd);
					free(arraydoc);
					free (read);
					exit(0);
					// update_exit_status_and_exit(0);
				}
			}
			arraydoc = ft_strjoin(arraydoc, read);
			arraydoc = ft_strjoin(arraydoc, "\n");
			free(read);
		}
	}
}

int	heredoc(t_commands *command_list)
{
	char	*read;
	char	*arraydoc;
	pid_t	pid;
	int		fd;

	fd = 0;
	signal_handler_heredoc(false);
	pid = fork();
	read = NULL;
	if (pid == 0)
	{
		arraydoc = NULL;
		prompt_loop(command_list, read, arraydoc, fd);
		if (fd >= 0)
			close(fd);
	}
	waitpid(pid, &g_megabash.exit_status, 0);
	// signal_handler_heredoc(false);
	if (fd >= 0)
		fd = open("./src/heredoc/heredoc_content", O_RDONLY, 0777);
	return (fd);
}
