#ifndef MINISHELL
# define MINISHELL

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>

typedef struct	s_root{
	char	*input;
	char	**command;
	void			*content;
	struct t_root	*next;
}				t_root;

//										megastart.c
void	megastart(t_root *root);

//										command_line.c
char	*command_line(t_root *root);

// 										space_treat.c
char	*original_cmd(char *cmd);
char	*treating_cmd(char *cmd);
char	**space_treat(char *input);

//										minishell_utils.c
void	free_matrix(char **matrix);
#endif
