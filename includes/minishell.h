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
# define TRUE 0
# define FALSE 1

typedef struct	s_env{
	char			*name;
	char			*content;
	struct s_env	*next;
}				t_env;

typedef struct s_commands
{
	char		**content;
	int			builtin;
	t_commands	*next;
}				t_commands;

typedef struct	s_global
{
	t_env		env;
	t_commands	cmd;
	char		*cmd_path;
	int			fd;
	int			exit_status;
}				t_global;

#endif
