/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalves <gusalves@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 20:57:29 by gusalves          #+#    #+#             */
/*   Updated: 2022/07/15 20:57:29 by gusalves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	child_is_builtin(char *input)
{
	if (!input)
		return (false);
	if (ft_new_strncmp("echo", input) == true)
		return (true);
	if (ft_new_strncmp("env", input) == true)
		return (true);
	if (ft_new_strncmp("pwd", input) == true)
		return (true);
	return (false);
}

int	parent_is_builtin(char *input)
{
	if (!input)
		return (false);
	if (ft_new_strncmp("export", input) == true)
		return (true);
	if (ft_new_strncmp("unset", input) == true)
		return (true);
	if (ft_new_strncmp("cd", input) == true)
		return (true);
	if (ft_new_strncmp("exit", input) == true)
		return (true);
	return (false);
}
