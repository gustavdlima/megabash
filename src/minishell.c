#include "minishell.h"

t_global	g_megabash;

static void	megaexecute(char **input)
{
	treat_input(input);
	print_token(g_megabash.token_list);
	parsing();
	print_commands(g_megabash.cmd_list);
	export(g_megabash.cmd_list->content);
	g_megabash.exit_status = 0;
}

static void	megastart(void)
{
	char	*input;

	while (1)
	{
		signal_handler();
		input = read_input();
		printf("\n\ninput: %s\n", input);
		if (validate_input(input) == TRUE)
			megaexecute(&input);
		else
			printf("BORN TO BE BASH\n");
		// create_list(read);
		// free_megabash();
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
