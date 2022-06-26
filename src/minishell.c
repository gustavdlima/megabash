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

void	redirection_output_append(t_commands	*pivot)
{
	int	outfile;

	while (pivot->redirect)
	{
		dprintf(2, "pivot.cmd : %s\n redirect.content : %s\n", pivot->cmd, pivot->redirect->content);
		if (pivot->redirect->content && pivot->redirect->type == is_output)
			outfile = open(pivot->redirect->content,  O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (pivot->redirect->content && pivot->redirect->type == is_append)
			outfile = open(pivot->redirect->content, O_WRONLY | O_CREAT | O_APPEND, 0777);
		pivot->redirect = pivot->redirect->next;
	}
	check_dup(outfile, STDOUT_FILENO);
}

void	child_proccess(t_commands *pivot, int **fd, int i)
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
	if (pivot->redirect)
	{
		dprintf(2,"TO NA CONDICAO!\n");
		redirection_output_append(pivot);
	}
	if (child_is_builtin(pivot->cmd) == true)
		execute_builtin(pivot);
	else
		execute_execve(pivot);
}

void	execute_multiple_commands(void)
{
	int		**fd;
	int		i;
	pid_t	pid;
	t_commands	*pivot;

	pivot = g_megabash.cmd_list;
	fd = malloc_int_matrix();
	i = 0;
	while (fd[i])
	{
		if (pipe(fd[i]) == -1)
		{
			error_message_exit("Proccess error : pipe", 1);
			exit(1);
		}
		i++;
	}
	i = 0;
	while (pivot)
	{
		if (parent_is_builtin(pivot->cmd) == true)
		{
			execute_builtin(pivot);
			i++;
			pivot = pivot->next;
			continue ;
		}
		pid = fork();
		if (pid == 0)
			child_proccess(pivot, fd, i);
		if (fd[i])
			close(fd[i][1]);
		i++;
		pivot = pivot->next;
	}
	i = 0;
	while (i++ < g_megabash.pipe + 1)
		waitpid(-1, &g_megabash.exit_status, 0);
}

void	execute_single_command(void)
{
	pid_t		pid;
	t_commands	*pivot;

	pivot = g_megabash.cmd_list;
	if (parent_is_builtin(pivot->cmd) == true)
	{
		execute_builtin(pivot);
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		if (pivot->redirect)
		{
			dprintf(2,"TO NA CONDICAO!\n");
			redirection_output_append(pivot);
		}
		if (child_is_builtin(pivot->cmd))
			execute_builtin(pivot);
		else
			execute_execve(pivot);
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
	// print_commands(g_megabash.cmd_list);
	if (ft_new_strncmp("exit", g_megabash.cmd_list->cmd) == true
		&& g_megabash.pipe == 0)
		exit_the_program(g_megabash.cmd_list->content);
	else
		executing_processes();
}

static void	megastart(void)
{
	char	*input;

	while (1)
	{
		signal_handler();
		input = read_input();
		// printf("\n\ninput: %s\n", input);
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
