#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>

# define TRUE 0
# define FALSE 1

typedef	struct	s_env{
	char			*name;
	char			*content;
	struct s_env	*next;
}				t_env;

typedef struct s_commands
{
	char				**content;
	int					builtin;
	struct s_commands	*next;
}				t_commands;

typedef struct	s_global
{
	t_env		*env;
	t_commands	*cmd;
	char		*cmd_path;
	int			fd;
	int			exit_status;
}				t_global;

# include "environment.h"
# include "linked_list.h"
# include "utils.h"

extern t_global	g_megabash;

#endif
