#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

void		parsing(void);
t_token *command_parse(t_token *token, t_commands *command);

#endif
