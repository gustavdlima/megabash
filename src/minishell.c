#include "minishell.h"

t_global	g_megabash;

void	megastart(void)
{
	char	*read;

	while (1)
	{
		signal_handler();
		read = read_input();
		if (validate_input(read) == TRUE)
			treat_input(&read);
		else
			printf("BORN TO BE BASH\n");
		printf ("INPUT = %s\n", read);
		create_list(read);
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
