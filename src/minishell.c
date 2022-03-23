#include "minishell.h"

t_global	g_megabash;

void	megastart(void)
{

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
