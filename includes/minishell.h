#ifndef MINISHELL
# define MINISHELL

# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>


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

//										init_struct.c
void	initialize_struct(t_root *root, char **envp);

//										line_input_treat.c
void	input_treat(t_root *root);

//										megastart.c
void	megastart(t_root *root, t_env *env);

//										metacharacters_treat.c
/* do not interpret \ or ; */
int		special_characters(char *cmd);
/* looks for $ to interpret */
char	*metacharacters_treat(char *cmd);

//										env.c
t_env	*environment(t_root *root);
char	*get_env_name(char *envp);
char	*get_env_path(char *envp);
void 	put_env_data(char *envp, t_env *env);

//										check_builtins.c
int	check_builtins(t_root *root, t_env *env);

//										builtins

//										builtin_export.c
void	export(t_root *root, t_env *env);
char	*get_export_data_name(char *data);
char	*get_export_data_content(char *data);
char	*remove_quotes(char *data);

//										env_operations.c
void			env_content_to_null(t_env *list, char *name);
void			env_node_addback(t_env *list, char *name, char *content);
void			env_node_delete(t_env *list, char *name);
struct s_env 	*get_env_node(t_env *list, char *name, int size);
void	print_env(t_env *env);

//										process.c
// void	child_process(t_root *root, int *fd);
// void	parent_process(t_root *root, int *fd);

//										execute_process.c
void	execute_process(t_root *root, t_env *env);

//										command_line.c
void	command_line(t_root *root);
char	*what_cmd(char *cmd, t_env *env);

//										quotes_treat.c
char	*reverse_quotes_treat(char *cmd);
char	*quotes_treat(char *cmd);
/* taking off quotes to show the right output*/
char	*no_quotes(char *cmd);
/* verifies if quotes are matching*/
int		matching_quotes(char *cmd);
/* looks for double quotes arguments*/
int		double_quotes(char *cmd);

//										redirections_treat.c
void		find_redirections(t_root *root);

// 										space_treat.c
char	*space_treat(char *cmd, char sign);
char	**reverse_space_treat(char **matrix);
char	**matrix_split(char *cmd, int cmd_size);

//										minishell_utils.c
void	free_matrix(char **matrix);
int		ft_int_strchr(const char *s, int c);

//										lst_utils.c
int		env_lstsize(t_env *lst);
void	env_addback(t_env **lst, t_env *new);
t_env	*env_lstnew(char *name, char *content);
t_env	*env_last_node(t_env *lst);
int		env_name_check(t_env *lst, char *name);

#endif
