#include "minishell.h"

t_global	g_megabash;

void	destroy_heredocs_fd(void)
{
	t_commands	*pivot;

	pivot = g_megabash.cmd_list;
	while (pivot)
	{
		if (pivot->redirect && pivot->redirect->type == is_here_doc)
			unlink("./src/heredoc/heredoc_content");
		pivot = pivot->next;
	}
}

void	executing_processes(void)
{
	if (g_megabash.pipe == 0)
		execute_single_command();
	else
		execute_multiple_commands();
	destroy_heredocs_fd();
}

static void	megaexecute(char **input)
{
	g_megabash.pipe = 0;
	treat_input(input);
	// print_token(g_megabash.token_list);
	parsing();
	free_token(g_megabash.token_list);
	// print_commands(g_megabash.cmd_list);
	if (g_megabash.cmd_list->cmd && ft_new_strncmp("exit", g_megabash.cmd_list->cmd) == true
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
		input = read_input();
		// printf("\n\ninput: %s\n", input);
		if (input && validate_input(input) == true)
			megaexecute(&input);
		else
			printf("BORN TO BE BASH\n");
		// 	free(input);
		// else
			// free(g_megabash.last_input);
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
