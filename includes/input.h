/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmilson- <jmilson-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 21:05:58 by gusalves          #+#    #+#             */
/*   Updated: 2022/07/22 19:45:42 by jmilson-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# include "minishell.h"

// read_input.c
char	*read_input(void);
int		only_space(char *cmd);
int		different_redirection_signs(char *cmd);
int		no_words_after_redirect(char *input);

// treat_input.c
void	treat_input_and_tokenizer(char **input);
void	treat_input_chars(char *input);
int		check_operator(char operator);
int		is_operator(char *input);

// validate_input.c
int		validate_input(char *input);

// expand_env.c
int		jump_positions(char *cmd);
char	*treat_dollar(char *cmd);

// is_builtin.c
int		parent_is_builtin(char *input);
int		child_is_builtin(char *input);

// check_input.c
void	check_input(void);

// treat_operators.c
char	*treat_operators(char *input);
char	*check_operator_space(char *input);

#endif
