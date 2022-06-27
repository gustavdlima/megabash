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
int		ft_new_strncmp(char *s1, char *s2);
int		ft_int_strchr(const char *s, int c);
int		matrix_size(char **matrix);
char	*insert_caracter(char *cmd, char caracter);
int		is_alphabetic(char *str);

//validate_pipes_utils.c
int		pipe_no_arguments(char *cmd);

//validate_redirect_utils.c
int		different_redirection_signs(char *cmd);
int		redirect_to_no_arguments(char *cmd);
int		too_many_redirections(char *cmd);

// validate_utils.c
int		open_curly_bracket(char *cmd);
int		open_quotes(char *cmd);
int		bash_syntax_error(char *cmd);
int		command_not_found(char *cmd);

// exit_status.c
void	error_message(char *msg, int exit_status);
void	error_message_exit(char *message, int exit_status);

// builtin_utils.c
int	execute_builtin(t_commands *cmd_list);
int	parent_execute_builtin(t_commands *cmd_list);

// execute_utils.c
void	execute_execve(t_commands *cmd_list);
int		**malloc_int_matrix(void);
int		check_dup(int old, int new);

#endif
