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
# define FALSE 1
# define TRUE 0

typedef struct	s_env{
	char			*name;
	char			*content;
	struct s_env	*next;
}				t_env;

typedef struct s_command
{
	char				**content;
	struct s_command	*next;
}				t_command;


typedef struct s_global
{
	t_env		*env;
	t_command	*cmd;
	char		*input;
	char		**envp;
	char		*cmd_path;
}				t_global;

t_global	g_megabash;

//										init_struct.c
void	initialize_struct(char **envp);

//										line_input_treat.c
void	input_treat(void);

//										megastart.c
void	megastart(void);

//										metacharacters_treat.c
/* do not interpret \ or ; */
int		special_or_metacharacters(char *cmd);
/* looks for $ to interpret */
char	*metacharacters_treat(char *cmd);
char	*interpret_dollar(char *cmd, int position);

//										env.c
t_env	*environment(char **envp);
char	*get_env_name(char *envp);
char	*get_env_path(char *envp);
void 	put_env_data(char *envp, t_env *env);

//										env_operations.c
void			env_content_to_null(t_env *list, char *name);
void			env_node_addback(t_env *list, char *name, char *content);
void			env_node_delete(t_env *list, char *name);
struct s_env 	*get_env_node(t_env *list, char *name);

//										process.c
// void	child_process(t_root *root, int *fd);
// void	parent_process(t_root *root, int *fd);

//										execute_process.c
void	execute_process(void);

//										expand_utils.c
struct s_env *get_env_content_(char *cmd);
int		jump_positions(char *cmd);

//										command_line.c
void	command_line(void);
char	*what_cmd(char *cmd);

//										quotes_treat.c
char	*reverse_quotes_treat(char *cmd);
char	*quotes_treat(char *cmd);
/* taking off quotes to show the right output*/
char	*no_quotes(char *cmd);
/* verifies if quotes are matching*/
int		matching_quotes(char *cmd);
/* looks for double quotes arguments*/
int		double_closed_quotes(char *cmd);

//										redirections_treat.c
void		find_redirections(void);
/*it looks for <<*/
int			theres_delimiter(char *cmd);

// 										space_treat.c
char	*space_treat(char *cmd, char sign);
char	**reverse_space_treat(char **matrix);
char	**tokenizer(char *cmd, int cmd_size);

//										minishell_utils.c
void	free_matrix(char **matrix);
void	free_linked_list(t_env *env);
int		ft_int_strchr(const char *s, int c);

//										lst_utils.c
int		env_lstsize(t_env *lst);
void	env_addback(t_env **lst, t_env *new);
t_env	*env_lstnew(char *name, char *content);
t_env	*env_last_node(t_env *lst);
int		env_name_check(t_env *lst, char *name);

//										pipe_treat.c
int		find_pipe(char *cmd);
void	pipe_treat(void);

#endif
