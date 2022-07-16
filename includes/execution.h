/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalves <gusalves@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 21:05:47 by gusalves          #+#    #+#             */
/*   Updated: 2022/07/15 21:05:47 by gusalves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"

void	initialize_execution_process(int **fd);
void	executing_processes(void);
void	execute_single_command(void);
void	execute_multiple_commands(void);
void	child_proccess(t_commands *pivot, int **fd, int i);
int		redirect_commands(t_redirect *pivot, int heredoc_fd);
void	initialize_process(int **fd);
void	destroy_heredocs_fd(void);
void	execute_command_and_redirection(t_commands *pivot, int heredoc_fd);
int		redirect_commands_no_pipes(t_redirect *pivot);
void	execute_command_and_redirection_no_pipes(t_commands *pivot);
#endif
