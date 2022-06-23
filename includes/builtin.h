#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"

void	b_exit(char *input);
void	export(char **command);
void	unset(char **command);
void	pwd(char **command);
void	free_unset(t_env *list);
void	cd(char **matrix);
void	builtin_env(char **matrix);
void	echo(char **matrix);

#endif
