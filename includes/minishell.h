#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <signal.h>

# define TRUE 1
# define FALSE 0

# define IS_BUILTIN		10
# define IS_CMD			11
# define IS_PIPE		12
# define IS_REDIRECT	13
# define IS_HERE_DOC	14
# define IS_FILE		15
# define IS_PARAMETER	16

typedef	struct	s_env{
	char			*name;
	char			*content;
	struct s_env	*next;
}				t_env;

typedef struct	s_token{
	int					type;
	char			*content;
	struct s_token	*next;
}				t_token;

typedef struct s_commands{
	int					type;
	char				*cmd;
	char				**content;
	char				*file;
	struct s_commands	*next;
}				t_commands;

typedef struct	s_global{
	t_env		*env;
	t_commands	*cmd_list;
	t_token		*token_list;
	char		**envp;
	char		*last_input;
	int			operation;
	int			pipe;
	int			tokens;
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
# include "command.h"
# include "parsing.h"

extern t_global	g_megabash;

#endif
