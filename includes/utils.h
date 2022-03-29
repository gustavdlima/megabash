#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"

//dolar_utils.c
char	*get_name(char *cmd);
char	*interpret_dollar(char *cmd, int position);
int		is_there_dollar(char *cmd, int max_i);
int		wheres_dollar(char *cmd);

//utils.c
int		ft_int_strchr(const char *s, int c);
int		matrix_size(char **matrix);

#endif
