#ifndef INPUT_H
# define INPUT_H

# include "minishell.h"

// read_input.c
char	*read_input(void);
int		too_many_pipes(char *cmd);
int		only_space(char *cmd);
int		is_it_history(char *cmd);
void	complete_input_properly(char **input);

// treat_input.c
void	treat_input(char **input);
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


int	too_many_pipes(char *cmd);
#endif
