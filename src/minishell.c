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

// static void	forking_input(int **matrix_fd, int *fd, int index)
// {
// 	pid_t	pid;
// 	char	*pathway;

// 	pid = fork();
// 	if (pid == -1)
// 		error_message("Deu ruim, boy...", 1);
// 	if (pid == 0)
// 	{
// 		// execute_execve(fd);
// 		pathway = what_cmd(g_megabash.cmd_list->cmd);
// 		if (!pathway)
// 			error_message("NÃO EXISTE!!", 1);
// 		check_dup(fd[0], STDIN_FILENO);
// 		check_dup(fd[1], STDOUT_FILENO);
// 	printf("OiiiiiiiiiiiiiiiiiiiiiiI\n");
// 		execve(pathway, g_megabash.cmd_list->content, g_megabash.envp);
// 	}
// 	else
// 	{
// 		pathway = what_cmd(g_megabash.cmd_list->cmd);
// 		if (!pathway)
// 			error_message("NÃO EXISTE!!", 1);
// 		// if (matrix_fd[index])
// 		// {
// 			check_dup(fd[1], STDIN_FILENO);
// 			// check_dup(matrix_fd[index][0], STDOUT_FILENO);
// 		// }
// 		// else
// 		// {
// 			check_dup(fd[0], STDIN_FILENO);
// 			check_dup(fd[1], STDOUT_FILENO);
// 		// }
// 	printf("OOOOOOOOOOOOOOOOOOOOOI\n");
// 		execve(pathway, g_megabash.cmd_list->content, g_megabash.envp);
// 	}
// 	print_commands(g_megabash.cmd_list);
// 	int	k = 0;
// 	while (k <= g_megabash.pipe - 1)
// 	{
// 		waitpid(pid, &g_megabash.exit_status, 0);
// 		k++;
// 	}
// 		g_megabash.cmd_list = g_megabash.cmd_list->next;
// }

static void	megaexecute(char **input)
{
	t_commands	*cmd_list;
	pid_t		pid;
	int			**fd;
	int			i;

	g_megabash.pipe = 0;
	treat_input(input);
	print_token(g_megabash.token_list);
	parsing();
	fd = malloc_int_matrix();
	cmd_list = g_megabash.cmd_list;
	// eu preciso de TRÊS loops: 1 LOOP PRA CRIAR TODOS OS PIPES DE UMA VEZ; OUTRO LOOP PARA CRIAR E EXECUTA-LOS (EXECVE) TODOS OS FORKS DE UMA VEZ; CRIAR LOOP DE WAIT;
	i = 0;
	while (i <= g_megabash.pipe - 1)
	{
		if (pipe(fd[i]) == -1)
		{
			g_megabash.exit_status = 1;
			write(2, "Process error\n", 15);
		}
		i++;
	}
	i = 0;
	while (i <= g_megabash.pipe - 1)
	{
		pid = fork();
		if (pid == 0)
		{
			if (i > 0)
			{
				dup2(fd[i][0], STDIN_FILENO);
				close(fd[i][0]);
			}
			if (i < g_megabash.pipe)
			{
				dup2(fd[i][1], STDOUT_FILENO);
				close(fd[i][1]);
			}
			if (execute_builtin() == false)
				execute_execve(cmd_list);
			dprintf(2, "pid 0 : %s\n", cmd_list->content);
		}
		else
		{
			if (i > 0)
			{
				dup2(fd[i - 1][0], STDIN_FILENO);
				close(fd[i - 1][0]);
			}
			if (i < g_megabash.pipe)
			{
				dup2(fd[i][1], STDOUT_FILENO);
				close(fd[i][1]);
			}
			if (execute_builtin() == false)
				execute_execve(cmd_list);
			dprintf(2, "pid : %s\n", cmd_list->content);
		}
		i++;
		cmd_list = cmd_list->next;
	}
	i = 0;
	while (i <= g_megabash.pipe - 1)
	{
		waitpid(-1, &g_megabash.exit_status, 0);
		i++;
	}
	if (g_megabash.pipe == 0)
	{
		if (execute_builtin() == false)
			execute_execve(cmd_list);
	}
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
