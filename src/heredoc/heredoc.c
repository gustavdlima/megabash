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
		signal_handler_heredoc(true);
		read = readline("> ");
		// if (ft_new_strncmp(command_list->redirect->content, read))
		if (read || ft_new_strncmp(command_list->redirect->content, read)) // TEM QUE REPETIR ENQUANTO NÃO FOR IGUAL O ARGUMENTO
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
	signal_handler_heredoc(false);
	pid = fork();
	read = ft_strdup("");
	if (pid == 0)
	{
		arraydoc = ft_strdup("");
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

// o que falta?
// criar um arquivo temporario e passar o conteudo do arraydoc para ele

// tenho que abrir um prompt usando readline ou read
// ao escrever, tenho que continuar abrindo prompt e ir guardando ate
// escrever a palavra-chave

// caso mande varios heredocs, o ultimo eh que vai quitar..

// eh basicamente um loop de readline onde guarda e printa o conteudo colocado
// e espera a palavra-chave do readline ou um signal de ctrl + D ou ctrl + C
// ctrl c cancela a execucao
// ctrl d interrompe abruptamente e salva o que foi feito ate o momento

// usar fork pra poder abrir uma readline nova
