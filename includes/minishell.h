#ifndef MINISHELL
# define MINISHELL

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>

# define PATH "/usr/local/sbin/:/usr/local/bin/:/usr/sbin/:/usr/bin/:/sbin/:/bin/"

typedef struct	s_root{
	char	**command;
	char	**envp;
	char	*cmd_path;
	char	*path;
	char	*input;
}				t_root;

//										init_struct.c
void	initialize_struct(t_root *root, char **envp);

//										megastart.c
void	megastart(t_root *root);

//										process.c
// void	child_process(t_root *root, int *fd);
// void	parent_process(t_root *root, int *fd);

//										execute_process.c
void	execute_process(t_root *root);

//										command_line.c
void	command_line(t_root *root);
char	*what_cmd(char *cmd);

// 										space_treat.c
// char	*original_cmd(char *cmd);
// char	*treating_cmd(char *cmd);
char	*space_treat(char *cmd);
char	**reverse_space_treat(char **matrix);
char	**matrix_split(char *cmd, int cmd_size);

//										minishell_utils.c
void	free_matrix(char **matrix);
#endif
