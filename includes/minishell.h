#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <signal.h>

# define TRUE 0
# define FALSE 1

typedef	struct	s_env{
	char			*name;
	char			*content;
	struct s_env	*next;
}				t_env;

typedef struct	s_token{
	char			*content;
	struct s_token	*next;
}				t_token;

typedef struct s_commands{
	int					builtin;
	char				**cmd;
	struct s_commands	*next;
}				t_commands;

typedef struct	s_global{
	t_env		*env;
	t_commands	*cmd;
	t_token		*token_list;
	char		**envp;
	int			operation;
	int			exit_status;
}				t_global;

# include "environment.h"
# include "input.h"
# include "linked_list.h"
# include "utils.h"
# include "tokenizer.h"
# include "free.h"
# include "builtin.h"
# include "signal_handler.h"

void	megastart(void);

extern t_global	g_megabash;

#endif
