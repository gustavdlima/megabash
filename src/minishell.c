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
	int			*fd[2];
	int			i;

	g_megabash.pipe = 0;
	treat_input(input);
	print_token(g_megabash.token_list);
	parsing();
	cmd_list = g_megabash.cmd_list;
	// // eu preciso de TRÊS loops: 1 LOOP PRA CRIAR TODOS OS PIPES DE UMA VEZ; OUTRO LOOP PARA CRIAR E EXECUTA-LOS (EXECVE) TODOS OS FORKS DE UMA VEZ; CRIAR LOOP DE WAIT;
	// if (g_megabash.pipe == 0)
	// {
	if (pipe(fd[i]) == -1)
	{
		g_megabash.exit_status = 1;
		write(2, "Process error\n", 15);
	}
	pid = fork();
	if (pid == 0)
	{
		check_dup(cmd_list->content, STDIN_FILENO);
		check_dup(fd[1], STDOUT_FILENO);
		close(fd[0]);
		if (execute_builtin() == false)
			execute_execve(cmd_list);
	}
	close(fd[1]);
	waitpid(-1, &g_megabash.exit_status, 0);
	// check_dup(fd[0], STDIN_FILENO);
	// check_dup(1, STDOUT_FILENO);
	// close(fd[1]);
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
