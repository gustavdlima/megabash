#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

void		parsing(void);
t_commands	*take_command(t_token *token, t_commands *command);

#endif
