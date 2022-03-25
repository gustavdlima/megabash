#ifndef INPUT_H
# define INPUT_H

# include "minishell.h"

char	*read_input(void);
int		validate_input(char *input);
void	treat_input(char **input);
int		jump_positions(char *cmd, int position);

#endif
