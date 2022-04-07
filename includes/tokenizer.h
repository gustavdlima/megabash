#ifndef QUOTES_H
# define QUOTES_H

# include "minishell.h"

int	jump_special_or_metacharacters(char *cmd);
int	open_quotes(char *cmd);
int	single_quotted_argument(char *cmd, int dollar);
int	special_or_metacharacters(char c);
int	pipe_no_arguments(char *cmd);
char	*no_quotes(char *cmd);
int	ft_new_strncmp(char *s1, char *s2);
int	unquotted_special_metacharacters(char *cmd);

void	tokenizer (char *input);
void	treat_token_list(void);

#endif
