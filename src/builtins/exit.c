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

static void	free_exit_builtin(void)
{
	free_megabash();
	free_env(g_megabash.env);
	rl_clear_history();
	free(g_megabash.last_input);
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
	while(str[i])
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
		if (str_long )
		return (true);
	}
	return (false);
}

void	exit_the_program(char *input)
{
	char	**matrix;
	int		to_exit;
	int		matrix_len;
	char	*convert_number;

	matrix = ft_split(input, ' ');
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
		else if (check_arg(convert_number)
			&& !not_a_number(convert_number))
			g_megabash.exit_status = ft_atoi(convert_number);
		else if (!not_a_number(convert_number))
			g_megabash.exit_status = ft_atoi(convert_number);
		free(convert_number);
	}
	free_matrix(matrix);
	if (to_exit == true)
	{
		printf("exit\n");
		quit_megabash();
	}
}

void	b_exit(char **matrix)
{
	const int	matrix_len = matrix_size(matrix);

	if (matrix)
	{
		if (matrix_len > 1)
		{
			error_message("megabash error: exit: too many arguments", 1);
		}
		else if (matrix[1] && is_numeric(matrix[1]))
		{
			if (matrix[1] && !check_arg(matrix[1]))
				g_megabash.exit_status = ft_atoi(matrix[1]);
			free_exit_builtin();
		}
		else if (matrix[1])
		{
			error_message("megabash error: exit: numeric argument required", 1);
			free_exit_builtin();
		}
	}
	exit(g_megabash.exit_status);
}
