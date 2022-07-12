#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"

typedef struct s_fd
{
	int			outfile;
	int			infile;
	int			is_input;
	int			is_out_or_append;
	int			is_valid_fd;
	int			execute_input;
	int			execute_out_or_append;
}				t_fd;


void	initialize_execution_process(int **fd);
void	executing_processes(void);
void	execute_single_command(void);
void	execute_multiple_commands(void);
void	child_proccess(t_commands *pivot, int **fd, int i);
int		redirect_commands(t_commands	*pivot);
void	initialize_process(int **fd);
void	destroy_heredocs_fd(void);
void	execute_command_and_redirection(t_commands *pivot);
#endif
