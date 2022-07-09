#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"

void	b_exit(char **matrix);
void	exit_the_program(char **matrix);
void	export(char **command);
void	unset(char **command);
void	pwd(char **command);
void	free_unset(t_env *list);
void	cd(char **matrix);
void	new_pwd_env(void);
void	new_oldpwd_env(void);
void	builtin_env(char **matrix);
void	echo(char **matrix);
int		is_numeric(char *string);

#endif
