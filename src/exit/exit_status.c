/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalves <gusalves@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 20:52:19 by gusalves          #+#    #+#             */
/*   Updated: 2022/07/15 20:52:55 by gusalves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	quit_megabash(void)
{
	free_token(g_megabash.token_list);
	free_commands(g_megabash.cmd_list);
	free_env(g_megabash.env);
	rl_clear_history();
	exit(g_megabash.exit_status);
}
