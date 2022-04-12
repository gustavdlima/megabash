#ifndef INPUT_H
# define INPUT_H

# include "minishell.h"

// read_input.c
char	*read_input(void);
int		only_space(char *cmd);

// treat_input.c
void	treat_input(char **input);
void	command_list(void);
int		check_operator(char operator);
void	process_exec(char *input);
int		is_operator(char *input);
int		validate_input(char *input);
int		jump_positions(char *cmd);
int		wheres_dollar(char *cmd);
void	treat_space(char *cmd);
void	treat_char(char *cmd, char c, int nbr);
void	reverse_char(char *cmd, int nbr, char c);
void	reverse_input_chars(char *input);
void	treat_input_chars(char *input);
char	*treat_dollar(char *cmd);
int		treat_dollar_input(char *cmd, char **final, char **temp,
			char **sec_temp, char *input);
int		is_builtin(char *input);
void	check_input(void);

// treat_operators.c
char	*treat_operators(char *input);
char	*check_operator_space(char *input);
#endif
