#include "minishell.h"

t_global	g_megabash;

static void	megaexecute(char **input)
{
	treat_input(input);
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
		printf ("INPUT = %s\n", input);
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
	environment(envp);
	megastart();
	return (0);
}
