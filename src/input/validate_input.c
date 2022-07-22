/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmilson- <jmilson-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 20:57:47 by gusalves          #+#    #+#             */
/*   Updated: 2022/07/22 19:26:10 by jmilson-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	theres_break_line(char *input)
{
	char	*temp;

	temp = ft_strtrim(input, " ");
	if (!ft_strncmp("/n", temp, 2))
	{
		free(temp);
		return (true);
	}
	if (temp)
		free(temp);
	return (false);
}

static int	should_validate(char *input)
{
	if (!input || only_space(input) == true)
		return (false);
	else if (bash_syntax_error(input) == true)
		return (false);
	else if (different_redirection_signs(input) == true)
		return (false);
	else if (too_many_redirections(input) == true)
		return (false);
	else if (redirect_to_no_arguments(input) == true)
		return (false);
	else if (no_words_after_redirect(input) == true)
		return (false);
	else if (pipe_no_arguments(input) == true)
		return (false);
	else if (theres_break_line(input) == true)
		return (false);
	if (open_quotes(input) == true)
	{
		error_message("MEGABASH :  syntax error : There's an open quote", 2);
		return (false);
	}
	return (true);
}

int	validate_input(char *input, int is_valid)
{
	if (is_valid && input)
	{
		treat_input_chars(input);
		if (input)
		{
			if (should_validate(input))
				return (true);
		}
	}
	return (false);
}
