#ifndef QUOTES_H
# define QUOTES_H

# include "minishell.h"

int	unquotted_command(char *cmd);
int	open_quotes(char *cmd);
int	special_or_metacharacters(char *cmd);
#endif
