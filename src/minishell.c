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
	while (g_megabash.cmd_list)
	{
		pid = fork();
		if (pid == 0)
		{
			if (i != 0)
			{
				check_dup(fd[i - 1][0], STDIN_FILENO);
			}
			// else
			check_dup(fd[i][1], STDOUT_FILENO);
			if (is_builtin(g_megabash.cmd_list->cmd))
				execute_builtin();
			else
				execute_execve(g_megabash.cmd_list);
		}
		
		if (fd[i + 1])
			i++;
		g_megabash.cmd_list = g_megabash.cmd_list->next;
	}
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
	t_commands	*cmd_list;
	pid_t		pid;
	int			**fd;

	g_megabash.pipe = 0;
	treat_input(input);
	// print_token(g_megabash.token_list);
	parsing();
	executing_processes();
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
