#ifndef FREE_H
# define FREE_H

# include "minishell.h"

void	free_matrix(char **matrix);
void	free_int_matrix(int **matrix);
void	free_env(t_env *env);
void	free_megabash(void);
void	free_cmd_megabash(void);

#endif
