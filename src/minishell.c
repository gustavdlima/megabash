#include "minishell.h"

t_global	g_megabash;

static void	megaexecute(char **input)
{
	printf("INPUTÃO: %s\n", *input);
		treat_input(input);
		check_input();
		g_megabash.exit_status = 0;
}

static void	megastart(void)
{
	char	*input;

	while (1)
	{
		signal_handler();
		input = read_input();
		if (validate_input(input) == TRUE)
			megaexecute(&input);
		else
			printf("BORN TO BE BASH\n");
		print_token(g_megabash.token_list);
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
