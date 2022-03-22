#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	if (argc > 1 && argv != NULL)
	{
		printf("Error. Try only ./minishell\n");
		exit (1);
	}
	// g_megabash.input->envp = envp;
	g_megabash.env = environment(envp);
	megastart();
}
