#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "minishell.h"

int				jump_special_or_metacharacters(char *cmd);
int				single_quotted_argument(char *cmd, int dollar);
int				special_or_metacharacters(char c);
char			*no_quotes(char *cmd);
int				unquotted_special_metacharacters(char *cmd);
void			treat_quote(char *cmd);
void			set_token_type(t_token *list);
void			tokenizer(char *input);
void			treat_token_list(void);
struct s_token	*get_token_node(t_token *list, char *name);
t_token			*token_content_to_hell(t_token *list, char *name,
					char *true_name);

#endif
