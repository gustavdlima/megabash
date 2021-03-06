/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmilson- <jmilson-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 21:07:13 by gusalves          #+#    #+#             */
/*   Updated: 2022/07/17 03:48:26 by jmilson-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"

//dolar_utils.c
char	*interpret_dollar(char *cmd, int position);
int		is_question_mark(char *cmd);
int		is_there_dollar(char *cmd);
int		wheres_dollar(char *cmd);
int		single_dollar(char *cmd);

//treat_input_utils.c
char	*get_name(char *cmd);
void	treat_char(char *cmd, char c, int nbr);
void	reverse_char(char *cmd, int nbr, char c);
void	reverse_input_chars(char *input);
char	*double_operator(char *input, int i, int is_second_space);

//utils.c
int		ft_new_strncmp(char *s1, char *s2);
int		ft_int_strchr(const char *s, int c);
int		matrix_size(char **matrix);
char	*insert_caracter(char *cmd, char caracter);
int		is_alphabetic(char *str);

//validate_redirect_utils.c
int		redirect_to_no_arguments(char *cmd);
int		too_many_redirections(char *cmd);

// validate_utils.c
int		open_curly_bracket(char *cmd);
int		open_quotes(char *cmd);
int		bash_syntax_error(char *cmd);
int		pipe_no_arguments(char *cmd);
int		no_words_after_redirect(char *input);

// exit_status.c
void	error_message(char *msg, int exit_status);
void	error_message_exit(char *message, int exit_status);
void	update_exit_status_and_exit(int exit_status);
void	quit_megabash(void);
void	waitipid_save_exit_status(int pid);

// execute_utils.c
int		**malloc_int_matrix(int **fd);
int		check_and_dup(int old, int new);
char	*what_cmd(char *cmd);

// validate_input.c
int		only_quotes(char *cmd);
#endif
