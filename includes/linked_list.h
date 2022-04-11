#ifndef LINKED_LIST_H
# define LINKED_LIST_H

# include "minishell.h"

t_env	*env_lst_new(char *name, char *content);
int		env_name_check(t_env *lst, char *name);
void	env_addback(t_env **lst, t_env *new);
t_env	*env_last_node(t_env *lst);
int		env_lst_size(t_env *lst);

t_commands	*cmd_lst_new(void);
t_commands	*cmd_lst_new_args(char *cmd);
void	cmd_addback(t_commands **lst, t_commands *new);
t_commands	*cmd_last_node(t_commands *lst);
void	free_commands(t_commands *commands);
void	print_commands(t_commands *commands);

t_token	*token_lst_new(char *content);
void	token_addback(t_token **lst, t_token *new);
t_token	*token_last_node(t_token *lst);
int token_pipe_checker(t_token *token);
void	print_token(t_token *token);
void	free_token(t_token *token);

#endif
