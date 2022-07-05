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
	parsing();
	free_token(g_megabash.token_list);
	if (g_megabash.cmd_list->cmd && ft_new_strncmp("exit", g_megabash.cmd_list->cmd) == true && g_megabash.pipe == 0)
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
		input = readline("\033[0;35mmegabash$ \033[0m");
		if (input)
		{
			complete_input_properly(&input);
		}
		else
		{
			ft_putendl_fd("exit", STDOUT_FILENO);
			rl_clear_history();
			if (g_megabash.last_input)
				free(g_megabash.last_input);
			if (g_megabash.env)
				free_env(g_megabash.env);
			// if (g_megabash.cmd_list)
			// 	free_cmd_megabash();
			exit(0);
		}
		// input = read_input();
		if (input && validate_input(input) == true)
		{
			megaexecute(&input);
			free_megabash();
		}
		else
			printf("BORN TO BE BASH\n");
	}
}

int	main(int argc, char **argv, char **envp)
{
	if (argc > 1 && argv != NULL)
	{
		ft_putendl_fd("Error: Try only ./minishell", 2);
		exit(1);
	}
	g_megabash.last_input = NULL;
	environment(envp);
	megastart();
	return (0);
}
