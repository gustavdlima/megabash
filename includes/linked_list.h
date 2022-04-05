#ifndef LINKED_LIST_H
# define LINKED_LIST_H

# include "minishell.h"

t_env	*env_lst_new(char *name, char *content);
int		env_name_check(t_env *lst, char *name);
void	env_addback(t_env **lst, t_env *new);
t_env	*env_last_node(t_env *lst);
int		env_lst_size(t_env *lst);

t_commands	*cmd_lst_new(void);
#endif
