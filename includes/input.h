#ifndef INPUT_H
# define INPUT_H

# include "minishell.h"

char	*read_input(void);
void 	create_list(char *input);
void	process_exec(char *input);
int		is_operator(char *input);
int		validate_input(char *input);
void	treat_input(char **input);
int		jump_positions(char *cmd, int position);
int		wheres_dollar(char *cmd);
void	reverse_space(char *cmd);
<<<<<<< HEAD
=======
void	treat_space(char *cmd);
>>>>>>> 5e4bd6547455d6f7fd04c5f2d3a54fed90f065a1

#endif
