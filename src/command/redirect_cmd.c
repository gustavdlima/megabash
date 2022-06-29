#include "minishell.h"

int	valid_execution(int im_input, int im_out_or_append, int infile, int outfile)
{
	int	execute_im_input;
	int	execute_im_out_or_append;

	execute_im_input = 2;
	execute_im_out_or_append = 2;
	if (im_input)
		execute_im_input = check_and_dup(infile, STDIN_FILENO);
	if (im_out_or_append && execute_im_input)
		execute_im_out_or_append = check_and_dup(outfile, STDOUT_FILENO);
	if (execute_im_input != false && execute_im_out_or_append != false)
		return (true);
	else
		return (false);
}

int	open_fd_to_output_or_append(t_commands *pivot)
{
	int	outfile;

	if (pivot->redirect->type == is_output)
		outfile = open(pivot->redirect->content, O_WRONLY | O_CREAT
				| O_TRUNC, 0777);
	if (pivot->redirect->type == is_append)
		outfile = open(pivot->redirect->content, O_WRONLY | O_CREAT
				| O_APPEND, 0777);
	return (outfile);
}

int	redirect_commands(t_commands *pivot)
{
	int	outfile;
	int	infile;
	int	im_input;
	int	im_out_or_append;
	int	is_valid_fd;

	im_input = false;
	im_out_or_append = false;
	while (pivot->redirect)
	{
		if (pivot->redirect->type == is_input && pivot->redirect->content)
		{
			infile = open(pivot->redirect->content, O_RDONLY, 0777);
			im_input = true;
		}
		if (pivot->redirect->content && (pivot->redirect->type == is_output
				|| pivot->redirect->type == is_append))
		{
			outfile = open_fd_to_output_or_append(pivot);
			im_out_or_append = true;
		}
		if (pivot->redirect->type == is_here_doc)
		{
			infile = heredoc(pivot);
			im_input = true;
		}
		pivot->redirect = pivot->redirect->next;
	}
	is_valid_fd = valid_execution(im_input, im_out_or_append, infile, outfile);
	return (is_valid_fd);
}
