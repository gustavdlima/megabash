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
	int	outfile;
	int	infile;
	int	im_input;
	int	im_out_or_append;
	int	is_valid_fd;
	t_redirect *temp;

	temp = pivot->redirect;
	im_input = false;
	im_out_or_append = false;
	while (temp)
	{
		if (temp->type == is_input && temp->content)
		{
			infile = open(temp->content, O_RDONLY, 0777);
			im_input = true;
		}
		if (temp->type == is_output || temp->type == is_append)
		{
			if ((im_input == true && infile >= 0) || im_input == false)
				outfile = open_fd_to_output_or_append(temp);
			im_out_or_append = true;
		}
		if (temp->type == is_here_doc)
			heredoc(temp);
		temp = temp->next;
	}
	is_valid_fd = valid_execution(im_input, im_out_or_append, infile, outfile);
	return (is_valid_fd);
}
