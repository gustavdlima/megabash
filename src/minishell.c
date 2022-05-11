#include "minishell.h"

t_global	g_megabash;

static void	execute_execve(int *fd)
{
	char	*pathway;

	pathway = what_cmd(g_megabash.cmd_list->cmd);
	if (!pathway)
	{
		printf("NÃO EXISTE!!\n");
		g_megabash.exit_status = 1;
	}
	else
	{
		if (dup2(fd[0], STDIN_FILENO) != -1)
		{
			close(fd[0]);
			// if (dup2(fd[1], STDOUT_FILENO) != -1)
			// {
			// 	close(fd[1]);
			// }
		}
		execve(pathway, g_megabash.cmd_list->content, g_megabash.envp);
	}
	print_commands(g_megabash.cmd_list);
}

static void	forking_input(int *fd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		printf("deu ruim\n");
		g_megabash.exit_status = 1;
		exit (1);
	}
	if (pid == 0)
	{
		execute_execve(fd);
	}
	close(fd[1]);
	waitpid(pid, &g_megabash.exit_status, 0);
	close(fd[0]);
}

static void	megaexecute(char **input)
{
	int		fd[2];

	g_megabash.pipe = 0;
	treat_input(input);
	print_token(g_megabash.token_list);
	parsing();
	while (g_megabash.cmd_list)
	{
		if (g_megabash.pipe > 0 || g_megabash.cmd_list->redirect)
		{
			pipe(fd);
		}
		forking_input(fd);
		g_megabash.cmd_list = g_megabash.cmd_list->next;
	}
	// print_commands(g_megabash.cmd_list);
	// if(!ft_strncmp(g_megabash.cmd_list->cmd, "export", 7))
	// 	export(g_megabash.cmd_list->content);
	// if(!ft_strncmp(g_megabash.cmd_list->cmd, "unset", 6))
	// 	unset(g_megabash.cmd_list->content);
	// if (!ft_strncmp(g_megabash.cmd_list->cmd, "env", 4))
	// 	print_env(g_megabash.env);
	// if(!ft_strncmp(g_megabash.cmd_list->cmd, "pwd", 4))
	// 	pwd();
	// g_megabash.exit_status = 0;
}



static void	megastart(void)
{
	char	*input;

	while (1)
	{
		signal_handler();
		input = read_input();
		printf("\n\ninput: %s\n", input);
		if (input && validate_input(input) == true)
			megaexecute(&input);
		else
			printf("BORN TO BE BASH\n");
		// create_list(read);
		// free_megabash();
	}
}

int	main(int argc, char **argv, char **envp)
{
	if (argc > 1 && argv != NULL)
	{
		ft_putendl_fd("Error: Try only ./minishell", 2);
		exit(1);
	}
	g_megabash.last_input = ft_strdup("");
	environment(envp);
	megastart();
	return (0);
}
