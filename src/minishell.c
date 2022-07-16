/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalves <gusalves@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 21:04:14 by gusalves          #+#    #+#             */
/*   Updated: 2022/07/15 21:04:38 by gusalves         ###   ########.fr       */
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
	treat_input_and_tokenizer(input);
	parsing();
	free_token(g_megabash.token_list);
	executing_processes();
	free_commands(g_megabash.cmd_list);
}

static void	megastart(void)
{
	char	*input;

	while (1)
	{
		signal_handler();
		input = readline("megabash$ ");
		if (input)
			add_history(input);
		else
		{
			ft_putendl_fd("exit", STDOUT_FILENO);
			rl_clear_history();
			if (g_megabash.env)
				free_env(g_megabash.env);
			exit(0);
		}
		if (input && validate_input(input) == true)
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
