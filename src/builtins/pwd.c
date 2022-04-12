#include "minishell.h"

void	pwd(void)
{
	char	*directory;

	directory = getcwd(NULL, 0);
	if (directory)
		printf("%s\n", directory);
	free (directory);
}
