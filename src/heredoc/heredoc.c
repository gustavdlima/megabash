#include "minishell.h"

static void	save_data(char *content, int fd)
{
	fd = open("./src/heredoc/heredoc_content", O_WRONLY | O_CREAT | O_APPEND,
			0777);
	if (!content)
		write(fd, "", 1);
	else
		write(fd, content, ft_strlen(content));
}

static void	prompt_loop(t_redirect *command_list, char *read, char *arraydoc, int fd)
{
	t_redirect	*temp;

	temp = command_list;
	while (1)
	{
		signal_handler_heredoc();
		read = readline("> ");
		if (read && !ft_new_strncmp(temp->content, read))
		{
			arraydoc = ft_strjoin(read, "\n");
			free(read);
			save_data(arraydoc, fd);
			free(arraydoc);
		}
		else if (ft_new_strncmp(temp->content, read))
		{
			g_megabash.exit_status = 0;
			break ;
		}
		else
		{
			free_env(g_megabash.env);
			g_megabash.exit_status = 1;
			free(g_megabash.last_input);
			free_commands(g_megabash.cmd_list);
			exit(g_megabash.exit_status);
		}
	}
}

int	heredoc(t_redirect *command_list)
{
	char	*read;
	char	*arraydoc;
	pid_t	pid;
	int		fd;

	fd = 0;
	read = NULL;
	pid = fork();
	if (g_megabash.multiple_cmds == true)
		check_and_dup(g_megabash.stdin_backup, STDIN_FILENO);
	if (pid == 0)
	{
		arraydoc = NULL;
		prompt_loop(command_list, read, arraydoc, fd);
		free_commands(g_megabash.cmd_list);
		free_env(g_megabash.env);
		free(g_megabash.last_input);
		exit(0);
	}
	waitpid(pid, &g_megabash.exit_status, 0);
	// close(fd);
	fd = open("./src/heredoc/heredoc_content", O_RDONLY, 0777);
	// check_and_dup(fd, STDIN_FILENO);
	// dprintf(2, "EU TO AQUI!! /n");

	// close(fd);
	// free_env(g_megabash.env);
	unlink("./src/heredoc/heredoc_content");
	return (fd);
}
