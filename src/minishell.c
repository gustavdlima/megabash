#include "minishell.h"

int	main(int argc, char **argv __attribute__((unused)), char **envp)
{
	t_root	root;
	t_env	*env;


	if (argc > 1 && argv != NULL)
	{
		printf("Error. Try only ./minishell\n");
		exit (1);
	}
	// signal(SIGINT, handle_sigint);
	initialize_struct(&root, envp);
	env = environment(&root);
	megastart(&root, env);
}
