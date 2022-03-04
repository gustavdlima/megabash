#ifndef MINISHELL
# define MINISHELL

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <sys/wait.h>

typedef struct	s_root{
	char	*input;
	char	**parsed_input;
	void			*content;
	struct t_root	*next;
}				t_root;


#endif
