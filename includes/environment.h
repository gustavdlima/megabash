#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# include "minishell.h"

void	environment(char **envp);
char	*get_env_name(char *envp);
char	*get_env_path(char *envp);
void	print_env(t_env *env);

#endif
