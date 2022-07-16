/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalves <gusalves@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 20:52:09 by gusalves          #+#    #+#             */
/*   Updated: 2022/07/15 20:52:10 by gusalves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	valid_execution(int im_input, int im_out_or_append, int outfile,
	int infile)
{
	int	execute_im_input;
	int	execute_im_out_or_append;

	execute_im_input = 2;
	execute_im_out_or_append = 2;
	if (im_input)
		execute_im_input = check_and_dup(infile, STDIN_FILENO);
	unlink("./src/heredoc/heredoc_content");
	if (im_out_or_append && execute_im_input)
		execute_im_out_or_append = check_and_dup(outfile, STDOUT_FILENO);
	if (execute_im_input != false && execute_im_out_or_append != false)
		return (true);
	else
		return (false);
}

static int	open_fd_to_output_or_append(t_redirect *temp)
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

static int	open_fd_to_heredoc_or_input(t_redirect *temp, int fd_heredoc)
{
	int	infile;

	if (temp->type == is_here_doc)
	{
		if (fd_heredoc == -42)
			infile = heredoc(temp, NULL);
		else if (fd_heredoc != -1)
			infile = fd_heredoc;
	}
	if (temp->type == is_input)
		infile = open(temp->content, O_RDONLY, 0777);
	return (infile);
}

int	redirect_commands(t_redirect *pivot, int fd_heredoc)
{
	int	outfile;
	int	infile;
	int	im_input;
	int	im_out_or_append;
	int	is_valid_fd;

	im_input = false;
	im_out_or_append = false;
	while (pivot)
	{
		if (pivot->type == is_here_doc || pivot->type == is_input)
		{
			infile = open_fd_to_heredoc_or_input(pivot, fd_heredoc);
			im_input = true;
		}
		if (pivot->type == is_output || pivot->type == is_append)
		{
			if ((im_input == true && infile >= 0) || im_input == false)
				outfile = open_fd_to_output_or_append(pivot);
			im_out_or_append = true;
		}
		pivot = pivot->next;
	}
	is_valid_fd = valid_execution(im_input, im_out_or_append, outfile, infile);
	return (is_valid_fd);
}
