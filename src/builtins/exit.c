/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalves <gusalves@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 20:50:47 by gusalves          #+#    #+#             */
/*   Updated: 2022/07/16 00:58:01 by gusalves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_numeric(char *string)
{
	int	i;

	i = 0;
	while (string[i])
	{
		if (!ft_isdigit(string[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	check_arg(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (true);
		i++;
	}
	if (ft_atoi(arg) > 0 && ft_atoi(arg) <= 255)
		return (false);
	return (true);
}

int	not_a_number(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && str[i] != '-' && str[i] != '+')
			return (true);
		i++;
	}
	return (false);
}

int	too_long_number(char *str)
{
	int	str_int;
	int	str_long;

	str_int = ft_atoi(str);
	if (str_int == 0 && !ft_new_strncmp("0", str))
	{
		str_long = ft_atoli(str);
		if (str_long)
			return (true);
	}
	return (false);
}

void	builtin_exit(char **matrix)
{
	int		to_exit;
	int		matrix_len;
	char	*convert_number;

	matrix_len = matrix_size(matrix);
	to_exit = true;
	if (matrix_len > 1)
	{
		error_message("megabash error: exit: too many arguments", 1);
		to_exit = false;
	}
	else if (matrix[1])
	{
		convert_number = no_quotes(matrix[1]);
		if (not_a_number(convert_number) || too_long_number(convert_number))
		{
			error_message("megabash error: exit: numeric argument required", 2);
			to_exit = false;
		}
		else if ((check_arg(convert_number) && !not_a_number(convert_number))
			|| !not_a_number(convert_number))
			g_megabash.exit_status = ft_atoi(convert_number);
	}
	if (to_exit == true && g_megabash.pipe == 0)
		quit_megabash();
}
