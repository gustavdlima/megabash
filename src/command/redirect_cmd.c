#include "minishell.h"

int	redirect_commands(t_commands	*pivot)
{
	int	outfile;
	int	infile;
	int	im_input;
	int	im_out_or_append;
	int	execute_im_input;
	int	execute_im_out_or_append;

	im_input = false;
	im_out_or_append = false;
	execute_im_input = 2;
	execute_im_out_or_append = 2;
	while (pivot->redirect)
	{
		if (pivot->redirect->type == is_input)
		{
			if (pivot->redirect->content && pivot->redirect->type == is_input)
				infile = open(pivot->redirect->content, O_RDONLY, 0777);
			im_input = true;
		}
		if (pivot->redirect->type == is_output
			|| pivot->redirect->type == is_append)
		{
			dprintf(2, "pivot.cmd : %s\n redirect.content : %s\n", pivot->cmd, pivot->redirect->content);
			if (pivot->redirect->content && pivot->redirect->type == is_output)
				outfile = open(pivot->redirect->content,  O_WRONLY | O_CREAT | O_TRUNC, 0777);
			if (pivot->redirect->content && pivot->redirect->type == is_append)
				outfile = open(pivot->redirect->content, O_WRONLY | O_CREAT | O_APPEND, 0777);
			im_out_or_append = true;
		}
		pivot->redirect = pivot->redirect->next;
	}
	if (im_input)
		execute_im_input = check_dup(infile, STDIN_FILENO);
	if (im_out_or_append && execute_im_input)
		execute_im_out_or_append = check_dup(outfile, STDOUT_FILENO);
	if (execute_im_input != false && execute_im_out_or_append != false)
		return (true);
	else
		return (false);
}
