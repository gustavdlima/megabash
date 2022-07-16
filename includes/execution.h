/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalves <gusalves@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 21:05:47 by gusalves          #+#    #+#             */
/*   Updated: 2022/07/16 00:45:31 by gusalves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"

typedef struct s_redirect
{
	int					type;
	char				*content;
	struct s_redirect	*next;
}				t_redirect;

typedef struct s_commands
{
	int					type;
	char				*cmd;
	char				**content;
	struct s_redirect	*redirect;
	struct s_commands	*next;
}				t_commands;

// command list utils
t_commands	*cmd_lst_new(void);
t_commands	*cmd_lst_new_args(char *cmd);
void		cmd_lst_addback(t_commands **lst, t_commands *new);
t_commands	*cmd_last_node(t_commands *lst);
void		free_commands(t_commands *commands);
void		print_commands(t_commands *commands);

//token list utils
t_token		*token_lst_new(char *content);
void		token_addback(t_token **lst, t_token *new);
t_token		*token_last_node(t_token *lst);
int			token_pipe_checker(t_token *token);
void		print_token(t_token *token);
void		free_token(t_token *token);

//redirect list utils
t_redirect	*redirect_lst_new(void);
t_redirect	*redirect_last_node(t_redirect *lst);
void		redirect_addback(t_redirect **lst, t_redirect *new);
void		print_redirect(t_redirect *redirect);
void		free_redirect(t_redirect *redirections);
int			redirect_lst_size(t_redirect *lst);

// execution
void		execute_builtin(t_commands *cmd_list);
int			parent_execute_builtin(t_commands *cmd_list);
void		execute_execve(t_commands *cmd_list);
void		initialize_execution_process(int **fd);
void		executing_processes(void);
void		execute_single_command(void);
void		execute_multiple_commands(void);
void		child_proccess(t_commands *pivot, int **fd, int i);
int			redirect_commands(t_redirect *pivot, int heredoc_fd);
void		initialize_process(int **fd);
void		destroy_heredocs_fd(void);
void		execute_command_and_redirection(t_commands *pivot, int heredoc_fd);
int			redirect_commands_no_pipes(t_redirect *pivot);
void		execute_command_and_redirection_no_pipes(t_commands *pivot);

#endif
