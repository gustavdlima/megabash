#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"

//dolar_utils.c
char	*interpret_dollar(char *cmd, int position);
int		is_question_mark(char *cmd);
int		is_there_dollar(char *cmd, int max_i);
int		wheres_dollar(char *cmd);
int		single_dollar(char *cmd);

//treat_input_utils.c
char	*get_name(char *cmd);
int		treat_no_dollar_input(char *cmd, char **final, char **temp,
			char **sec_temp);

//utils.c
int		ft_int_strchr(const char *s, int c);
int		matrix_size(char **matrix);

#endif
