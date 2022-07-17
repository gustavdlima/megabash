/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmilson- <jmilson-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 21:01:02 by gusalves          #+#    #+#             */
/*   Updated: 2022/07/16 21:29:37 by jmilson-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	signint(int signum)
{
	(void)signum;
	dprintf(2, "\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_megabash.exit_status = 130;
}

static void	signint_doc(int signum)
{
	(void)signum;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	free_env(g_megabash.env);
	g_megabash.exit_status = 130;
	if (g_megabash.fd)
		free_int_matrix(g_megabash.fd);
	free_commands(g_megabash.cmd_list);
	exit(130);
}

void	signal_handler_heredoc(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGINT, signint_doc);
	signal(SIGQUIT, SIG_IGN);
}

static void	signint_child(int signum)
{
	(void)signum;
	g_megabash.exit_status = 130;
	dprintf(2, "\n");
}

static void	sigign_child(int signum)
{
	(void)signum;
	g_megabash.exit_status = 131;
	dprintf(2, "Quit\n");
}

void	signal_handler_child(void)
{
	signal(SIGINT, signint_child);
	signal(SIGQUIT, sigign_child);
}

void	signal_handler(void)
{
	signal(SIGINT, signint);
	signal(SIGQUIT, SIG_IGN);
}

// ◦ ctrl-C displays a new prompt on a new line.

// ◦ ctrl-D exits the shell.

// ◦ ctrl-\ does nothing.
