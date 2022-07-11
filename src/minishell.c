#include "minishell.h"

t_global	g_megabash;

static void	megaexecute(char **input)
{
	g_megabash.pipe = 0;
	if (ft_new_strncmp("exit", *input) == true && g_megabash.pipe == 0)
		exit_the_program(*input);
	treat_input_and_tokenizer(input);
	parsing();
	free_token(g_megabash.token_list);
	executing_processes();
	free_commands(g_megabash.cmd_list);
	// if (g_megabash.cmd_list->cmd && ft_new_strncmp("exit", g_megabash.cmd_list->cmd) == true && g_megabash.pipe == 0)
	// 	exit_the_program(g_megabash.cmd_list->content);
	// else
	// {
	// 	executing_processes();
	// 	free_commands(g_megabash.cmd_list);
	// }
}

static void	megastart(void)
{
	char	*input;

	while (1)
	{
		signal_handler();
		input = readline("✱ (≖ ͜ʖ≖) megabash ( ͡° ͜ʖ ͡°) ✱ $ ");
		if (input)
			add_history(input);
		else
		{
			ft_putendl_fd("exit", STDOUT_FILENO);
			rl_clear_history();
			if (g_megabash.last_input)
				free(g_megabash.last_input);
			if (g_megabash.env)
				free_env(g_megabash.env);
			exit(0);
		}
		if (input && validate_input(input) == true)
		{
			megaexecute(&input);
			if (g_megabash.exit_status == 256)
				g_megabash.exit_status = 127;
		}
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
