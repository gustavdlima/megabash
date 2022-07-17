/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_child.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmilson- <jmilson-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 23:35:48 by jmilson-          #+#    #+#             */
/*   Updated: 2022/07/16 23:36:32 by jmilson-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
