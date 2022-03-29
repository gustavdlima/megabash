#ifndef QUOTES_H
# define QUOTES_H

# include "minishell.h"

int	jump_special_or_metacharacters(char *cmd);
int	unquotted_command(char *cmd);
int	double_quotted_argument(char *cmd);
int	open_quotes(char *cmd);
int	single_quotted_argument(char *cmd);
int	special_or_metacharacters(char *cmd);
int	pipe_no_arguments(char *cmd);
#endif
