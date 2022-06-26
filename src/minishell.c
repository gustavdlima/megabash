#include "minishell.h"

t_global	g_megabash;

int	check_dup(int old, int new)
{
	if (dup2(old, new) == -1)
	{
		error_message("Permission denined or FD does not exists.\n", 1);
		return (false);
	}
	else
		close(old);
	return (true);
}

int	redirection_output_append(t_commands	*pivot)
{
	int	outfile;
	int	infile;
	int	im_input;
	int	im_out_or_append;
	int	execute_im_input;
	int	execute_im_out_or_append;

	im_input = false;
	im_out_or_append = false;
	execute_im_input = 2;
	execute_im_out_or_append = 2;
	while (pivot->redirect)
	{
		if (pivot->redirect->type == is_input)
		{
			if (pivot->redirect->content && pivot->redirect->type == is_input)
				infile = open(pivot->redirect->content, O_RDONLY, 0777);
			im_input = true;
		}
		if (pivot->redirect->type == is_output
			|| pivot->redirect->type == is_append)
		{
			dprintf(2, "pivot.cmd : %s\n redirect.content : %s\n", pivot->cmd, pivot->redirect->content);
			if (pivot->redirect->content && pivot->redirect->type == is_output)
				outfile = open(pivot->redirect->content,  O_WRONLY | O_CREAT | O_TRUNC, 0777);
			if (pivot->redirect->content && pivot->redirect->type == is_append)
				outfile = open(pivot->redirect->content, O_WRONLY | O_CREAT | O_APPEND, 0777);
			im_out_or_append = true;
		}
		pivot->redirect = pivot->redirect->next;
	}
	if (im_input)
		execute_im_input = check_dup(infile, STDIN_FILENO);
	if (im_out_or_append && execute_im_input)
		execute_im_out_or_append = check_dup(outfile, STDOUT_FILENO);
	if (execute_im_input != false && execute_im_out_or_append != false)
		return (true);
	else
		return (false);
}

void	child_proccess(t_commands *pivot, int **fd, int i)
{
	int	execute;

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
		execute = redirection_output_append(pivot);
	}
	if (child_is_builtin(pivot->cmd) == true && execute == true)
		execute_builtin(pivot);
	else if (execute == true)
		execute_execve(pivot);
	else
		exit(g_megabash.exit_status);
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
	int	execute;

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
			execute = redirection_output_append(pivot);
		}
		if (child_is_builtin(pivot->cmd) && execute == true)
			execute_builtin(pivot);
		else if (execute == true)
			execute_execve(pivot);
		else
			exit(g_megabash.exit_status);
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
