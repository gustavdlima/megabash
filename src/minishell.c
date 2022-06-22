#include "minishell.h"

t_global	g_megabash;

void	check_dup(int old, int new)
{
	if (dup2(old, new) == -1)
	{
		write(2, "Permission denined.\n", 21);
		g_megabash.exit_status = 1;
	}
	close(old);
}

void	execute_multiple_commands(void)
{
	int		**fd;
	int		i;
	pid_t	pid;

	fd = malloc_int_matrix();
	i = 0;
	while (fd[i])
	{
		if (pipe(fd[i]) == -1)
		{
			error_message("Proccess error : pipe", 1);
			exit(1);
		}
		i++;
	}
	i = 0;
	// t_commands cmd_list = g_megabash.cmd_list;
	while (g_megabash.cmd_list)
	{
		pid = fork();
		if (pid == 0)
		{
			if (i != 0)
			{
				close(fd[i - 1][1]);
				dup2(fd[i - 1][0], STDIN_FILENO);
				close(fd[i - 1][0]);
			}
			if (fd[i] != NULL)
			{
				close(fd[i][0]);
				dup2(fd[i][1], STDOUT_FILENO);
				close(fd[i][1]);
			}
			if (is_builtin(g_megabash.cmd_list->cmd))
				execute_builtin();
			else
			{
				dprintf(2, "i : %d\n", i);
				execute_execve(g_megabash.cmd_list);
				dprintf(2, "UÉ....\n");
			}
		}
		dprintf(2, "criou o fork O-O\n");
		if (fd[i])
			close(fd[i][1]);
		i++;
		g_megabash.cmd_list = g_megabash.cmd_list->next;
	}
	dprintf(2, "saiu do loop dos forks\n");
	i = 0;
	printf("pipes: %d\n", g_megabash.pipe);
	while (i < g_megabash.pipe + 1)
	{
		dprintf(2, "waiting for child proccess e.e\n");
		waitpid(-1, &g_megabash.exit_status, 0);
		dprintf(2, "past waitpid for child proccess e.e\n");
		i++;
	}
	dprintf(2, "saiu do loop do waitpid\n");
}

void	execute_single_command(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (is_builtin(g_megabash.cmd_list->cmd))
			execute_builtin();
		else
			execute_execve(g_megabash.cmd_list);
	}
	waitpid(pid, &g_megabash.exit_status, 0);
}

void	executing_processes(void)
{
	if (g_megabash.pipe == 0)
		execute_single_command();
	else
		execute_multiple_commands();
}

static void	megaexecute(char **input)
{
	g_megabash.pipe = 0;
	treat_input(input);
	// print_token(g_megabash.token_list);
	parsing();
	executing_processes();
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
	printf("ENTROU\n");
	megastart();
	return (0);
}
