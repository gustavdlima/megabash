#ifndef MINISHELL
# define MINISHELL

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>

# define PATH "/usr/local/sbin/::/usr/local/bin/:\
/usr/sbin/:/usr/bin/:/sbin/:/bin/"

typedef struct	s_root{
	char	**envp;
	char	**command;
	char	*input;
	void			*content;
	char	*path;
	struct t_root	*next;
}				t_root;

//										init_struct.c
void	initialize_struct(t_root *root, char **envp);

//										megastart.c
void	megastart(t_root *root);

//										command_line.c
char	*command_line(t_root *root);
char	*what_cmd(char *cmd);

// 										space_treat.c
char	*original_cmd(char *cmd);
char	*treating_cmd(char *cmd);
char	**space_treat(char *input);

//										minishell_utils.c
void	free_matrix(char **matrix);
#endif
