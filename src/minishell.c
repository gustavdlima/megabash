#include "minishell.h"

t_global	g_megabash;

void	check_dup(int a, int b)
{
	if (dup2(a, b) == -1)
	{
		write(2, "Permission denined.\n", 21);
		g_megabash.exit_status = 1;
	}
	close(a);
}

static void	forking_input(int **matrix_fd, int *fd, int index)
{
	pid_t	pid;
	char	*pathway;

	pid = fork();
	if (pid == -1)
		error_message("Deu ruim, boy...", 1);
	if (pid == 0)
	{
		// execute_execve(fd);
		pathway = what_cmd(g_megabash.cmd_list->cmd);
		if (!pathway)
			error_message("NÃO EXISTE!!", 1);
		check_dup(fd[0], STDIN_FILENO);
		check_dup(fd[1], STDOUT_FILENO);
	printf("OiiiiiiiiiiiiiiiiiiiiiiI\n");
		execve(pathway, g_megabash.cmd_list->content, g_megabash.envp);
	}
	else
	{
		pathway = what_cmd(g_megabash.cmd_list->cmd);
		if (!pathway)
			error_message("NÃO EXISTE!!", 1);
		if (matrix_fd[index])
		{
			check_dup(fd[1], STDIN_FILENO);
			check_dup(matrix_fd[index][0], STDOUT_FILENO);
		}
		else
		{
			check_dup(fd[0], STDIN_FILENO);
			check_dup(fd[1], STDOUT_FILENO);
		}
	printf("OOOOOOOOOOOOOOOOOOOOOI\n");
		execve(pathway, g_megabash.cmd_list->content, g_megabash.envp);
	}
	print_commands(g_megabash.cmd_list);
	int	k = 0;
	while (k <= g_megabash.pipe - 1)
	{
		waitpid(pid, &g_megabash.exit_status, 0);
		k++;
	}
}

static void	megaexecute(char **input)
{
	int		**fd;

	g_megabash.pipe = 0;
	treat_input(input);
	print_token(g_megabash.token_list);
	parsing();
	fd = (int **)ft_calloc(g_megabash.pipe, sizeof(int *));
	int l = g_megabash.pipe - 1;
	while (l >= 0)
	{
		fd[l] = ft_calloc(2, sizeof(int));
		l--;
	}
	while (g_megabash.cmd_list)
	{
		if (!ft_strncmp(g_megabash.cmd_list->cmd, "cd", 3))
		{
			cd(g_megabash.cmd_list->content);
			return;
		}
		if (!ft_strncmp(g_megabash.cmd_list->cmd, "env", 4))
		{
			builtin_env(g_megabash.cmd_list->content);
			return;
		}

		if (!ft_strncmp(g_megabash.cmd_list->cmd, "echo", 5))
		{
			echo(g_megabash.cmd_list->content);
			return;
		}
		if (!ft_strncmp(g_megabash.cmd_list->cmd, "unset", 6))
		{
			unset(g_megabash.cmd_list->content);
			return;
		}
		if (!ft_strncmp(g_megabash.cmd_list->cmd, "export", 7))
		{
			export(g_megabash.cmd_list->content);
			return;
		}
		if (!ft_strncmp(g_megabash.cmd_list->cmd, "exit", 5))
		{
			exit_builtin(g_megabash.cmd_list->content);
			return;
		}
		int i = 0;
		if (g_megabash.pipe > 0)
		{
			while (i <= g_megabash.pipe - 1)
			{
				// eu preciso de TRÊS loops: 1 LOOP PRA CRIAR TODOS OS PIPES DE UMA VEZ; OUTRO LOOP PARA CRIAR E EXECUTA-LOS (EXECVE) TODOS OS FORKS DE UMA VEZ; CRIAR LOOP DE WAIT;
				// criar todos os pipes
				pipe(fd[i]);
				i++;
			}
			int j = 0;
			while (j <= g_megabash.pipe - 1)
			{
				forking_input(fd, fd[j], j + 1);
				j++;
			}
		}
		else
		{
			char *pathway = what_cmd(g_megabash.cmd_list->cmd);
			if (!pathway)
				error_message("NÃO EXISTE!!", 1);
			execve(pathway, g_megabash.cmd_list->content, g_megabash.envp);
		}
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
