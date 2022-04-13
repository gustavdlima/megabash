#ifndef FREE_H
# define FREE_H

# include "minishell.h"

void	free_matrix(char **matrix);
void	free_env(t_env *env);
void	free_megabash(void);
void	free_strings(void *s1, void *s2, void *s3, void *s4, void *s5);

#endif
