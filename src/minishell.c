#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	if (argc > 1)
	{
		ft_putendl_fd("Error: Try only ./minishell", 2);
		exit(1);
	}
	(void)argv;
	(void)envp;
	return (0);
}
