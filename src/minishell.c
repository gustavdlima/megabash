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

static void	megaexecute(char **input)
{
	t_commands	*cmd_list;
	pid_t		pid;
	int			**fd;

	g_megabash.pipe = 0;
	treat_input(input);
	// print_token(g_megabash.token_list);
	parsing();
	// // eu preciso de TRÊS loops: 1 LOOP PRA CRIAR TODOS OS PIPES DE UMA VEZ; OUTRO LOOP PARA CRIAR E EXECUTA-LOS (EXECVE) TODOS OS FORKS DE UMA VEZ; CRIAR LOOP DE WAIT;
	cmd_list = g_megabash.cmd_list;
	// while (cmd_list != NULL)
	// {
	// 	pipe(fd);
	// pid = fork();
	// if (pid == 0)
	// {
	// 	close(fd[0]);
	// 	if (g_megabash.pipe > 0)
	// 	{
	// 		printf("EU TO PASSANO AQUI QUANDO DEVO\n");
	// 		dup2(fd[1], STDOUT_FILENO);
	// 	}
	// 	close(fd[1]);
	// 	execute_execve(cmd_list);
	// }
	// waitpid(pid, NULL, 0);
	// if (g_megabash.pipe > 0)
	// {
	// 	dup2(fd[0], STDIN_FILENO);
	// }
	// 	close(fd[0]);
	// 	close(fd[1]);
	// 	cmd_list = cmd_list->next;
	// 	i++;
	// }
	fd = malloc_int_matrix();
	int i = 0;
	while (fd[i])
	{
		if (pipe(fd[i]) == -1)
			error_message("Process error", 1);
		i++;
	}
	i = 0;
		cmd_list = g_megabash.cmd_list;
	while (fd[i])
	{
		pid = fork();
		if (pid == 0)
		{
			if (i > 0)
			{
				check_dup(fd[i - 1][0], STDIN_FILENO);
				check_dup(fd[i][1], STDOUT_FILENO);
			}
			else
			{
				// if (g_megabash.pipe > 0)
				// {
					// check_dup(fd[i + 1][1], STDOUT_FILENO);
					check_dup(fd[i][0], STDIN_FILENO);
				// }
			}
			printf("1\n");
			if (is_builtin(cmd_list->content) == true)
				execute_builtin();
			else
				execute_execve(cmd_list);
		}
		else
		{
			// if (i == 0)
				close(fd[i][1]);
			waitpid(pid, &g_megabash.exit_status, 0);
		}
		if (g_megabash.cmd_list && g_megabash.cmd_list->next)
			cmd_list = cmd_list->next;
		i++;
	}
}

static void	megastart(void)
{
	char	*input;
	int		fd_temp[2];

	while (1)
	{
		signal_handler();
		input = read_input();
		printf("\n\ninput: %s\n", input);
		if (input && validate_input(input) == true)
			megaexecute(&input);
		else
			printf("BORN TO BE BASH\n");
		// free_megabash();
		// free(input);
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
