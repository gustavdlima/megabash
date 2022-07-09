#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

void		parsing(void);
t_token		*cmd_parse(t_token *token, t_commands *command);
t_token	*redirect_parse(t_token *token, t_redirect *redirect);
int			redirect_type(char *content);
char		*cmd_operation(char *cmd_string, char *token_content);
t_commands	*copy_string_to_inside_matrix(t_commands *cmd_list, char *string);

#endif
