#include "minishell.h"

int	valid_execution(int im_input, int im_out_or_append, int outfile, int execute_im_input)
{
	int	execute_im_out_or_append;

	execute_im_out_or_append = 2;
	if (!im_input)
		execute_im_input = true;
	if (im_out_or_append && execute_im_input)
		execute_im_out_or_append = check_and_dup(outfile, STDOUT_FILENO);
	if (execute_im_input != false && execute_im_out_or_append != false)
		return (true);
	else
		return (false);
}

int	open_fd_to_output_or_append(t_redirect *temp)
{
	int	outfile;

	if (temp->type == is_output)
		outfile = open(temp->content, O_WRONLY | O_CREAT
				| O_TRUNC, 0777);
	if (temp->type == is_append)
		outfile = open(temp->content, O_WRONLY | O_CREAT
				| O_APPEND, 0777);
	return (outfile);
}

int	redirect_commands(t_commands *pivot)
{
	t_redirect	*temp;
	int			outfile;
	int			infile;
	int			is_input;
	int			is_out_or_append;
	int			is_valid_fd;
	int			execute_is_input;

	temp = pivot->redirect;
	is_input = false;
	is_out_or_append = false;
	while (temp)
	{
		if (temp->type == is_here_doc)
			heredoc(temp);
		if (temp->type == is_input)
		{
			infile = open(temp->content, O_RDONLY, 0777);
			execute_is_input = check_and_dup(infile, STDIN_FILENO);
			is_input = true;
		}
		if (temp->type == is_output || temp->type == is_append)
		{
			if ((is_input == true && infile >= 0) || is_input == false)
				outfile = open_fd_to_output_or_append(temp);
			is_out_or_append = true;
		}
		temp = temp->next;
	}
	is_valid_fd = valid_execution(is_input, is_out_or_append, outfile, execute_is_input);
	return (is_valid_fd);
}
