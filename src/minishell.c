#include "minishell.h"

int	main(int argc, char **argv __attribute__((unused)), char **envp)
{
	t_root	root;
	if (argc > 1)
	{
		printf("Error. Try only ./minishell\n");
		exit (1);
	}
	(void)envp;
	megastart(&root);
}
