#ifndef MINISHELL
# define MINISHELL

# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>

# define PATH "/usr/local/sbin/:/usr/local/bin/:/usr/sbin/:/usr/bin/:/sbin/\
				:/bin/"

typedef struct	s_env{
	char			*name;
	char			*content;
	struct s_env	*next;
}				t_env;

typedef struct s_root{
	char	**command;
	char	**envp;
	char	*cmd_path;
	char	*path;
	char	*input;
	char	*teste;
}				t_root;

#endif
