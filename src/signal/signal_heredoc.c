/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmilson- <jmilson-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 23:37:22 by jmilson-          #+#    #+#             */
/*   Updated: 2022/07/16 23:37:51 by jmilson-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	signint_doc(int signum)
{
	(void)signum;
	dprintf(2, "\n");
	free_env(g_megabash.env);
	g_megabash.exit_status = 130;
	if (g_megabash.fd)
		free_int_matrix(g_megabash.fd);
	free_commands(g_megabash.cmd_list);
	exit(130);
}

void	signal_handler_heredoc(void)
{
	signal(SIGINT, signint_doc);
	signal(SIGQUIT, SIG_IGN);
}
