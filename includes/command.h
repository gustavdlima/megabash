#ifndef COMMAND_H
# define COMMAND_H

# include "minishell.h"

char	*what_cmd(char *cmd);

void	execute_single_command(void);
void	execute_multiple_commands(void);
void	child_proccess(t_commands *pivot, int **fd, int i);

int		redirect_commands(t_commands	*pivot);

#endif
