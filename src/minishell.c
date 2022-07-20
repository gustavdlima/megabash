/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmilson- <jmilson-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 21:04:14 by gusalves          #+#    #+#             */
/*   Updated: 2022/07/19 23:47:26 by jmilson-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_global	g_megabash;

static void	print_cool_intro(void)
{
	int		fd;
	char	buff[1];

	fd = open("img/intro.txt", O_RDONLY);
	if (fd == -1)
		return ;
	while (read(fd, buff, 1))
	{
		printf("%c", buff[0]);
	}
	close(fd);
	return ;
}

static void	megaexecute(char **input)
{
	g_megabash.pipe = 0;
	g_megabash.fd = NULL;
	treat_input_and_tokenizer(input);
	parsing();
	free_token(g_megabash.token_list);
	executing_processes();
	if (g_megabash.cmd_list)
		free_commands(g_megabash.cmd_list);
}

static int	megabash_validation(char *input)
{
	int	is_valid;

	is_valid = true;
	if (open_quotes(input) == true)
	{
		error_message("MEGABASH :  syntax error : There's an open quote\n", 2);
		is_valid = false;
	}
	if (pipe_no_arguments(input) == true)
		is_valid = false;
	add_history(input);
	return (is_valid);
}

static void	megastart(void)
{
	char	*input;
	int		is_valid;

	while (1)
	{
		is_valid = true;
		signal_handler();
		input = readline("megabash$ ");
		if (input)
			is_valid = megabash_validation(input);
		if (!input)
		{
			ft_putendl_fd("exit", STDOUT_FILENO);
			rl_clear_history();
			if (g_megabash.env)
				free_env(g_megabash.env);
			exit(0);
		}
		if (input && validate_input(input, is_valid) == true)
			megaexecute(&input);
	}
}

int	main(int argc, char **argv, char **envp)
{
	if (argc > 1 && argv != NULL)
	{
		ft_putendl_fd("Error: Try only ./minishell", 2);
		exit(1);
	}
	print_cool_intro();
	environment(envp);
	megastart();
	return (0);
}
