#include "minishell.h"

static void	save_data(char *content, int fd)
{
	fd = open("./src/heredoc/heredoc_content", O_WRONLY | O_CREAT | O_TRUNC,
			0777);
	write(fd, content, ft_strlen(content));
}

static void	prompt_loop(t_commands *command_list, char *read, char *arraydoc, int fd)
{
	while (1)
	{
		read = readline("> ");
		if (read)
		{
			if (command_list->redirect->type == is_here_doc)
			{
				if (!ft_strncmp(command_list->redirect->content, read, ft_strlen(read)))
				{
					save_data(arraydoc, fd);
					free(arraydoc);
					break ;
				}
			}
			arraydoc = ft_strjoin(arraydoc, read);
			arraydoc = ft_strjoin(arraydoc, "\n");
			free(read);
		}
	}
	update_exit_status_and_exit(0);
}

int	heredoc(t_commands *command_list)
{
	char	*read;
	char	*arraydoc;
	pid_t	pid;
	int		fd;

	fd = 0;
	pid = fork();
	read = ft_strdup("");
	if (pid == 0)
	{
		arraydoc = ft_strdup("");
		prompt_loop(command_list, read, arraydoc, fd);
		close(fd);
	}
	waitpid(pid, &g_megabash.exit_status, 0);
	fd = open("./src/heredoc/heredoc_content", O_RDONLY, 0777);
	return (fd);
}
