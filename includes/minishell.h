/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalves <gusalves@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 21:06:46 by gusalves          #+#    #+#             */
/*   Updated: 2022/07/16 00:37:12 by gusalves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <signal.h>
# include "environment.h"
# include "input.h"
# include "linked_list.h"
# include "utils.h"
# include "tokenizer.h"
# include "free.h"
# include "builtin.h"
# include "signal_handler.h"
# include "execution.h"
# include "parsing.h"
# include "heredoc.h"

enum e_boolean
{
	false,
	true
};

enum e_types
{
	is_word = 12,
	is_pipe,
	is_redirect,
};

enum e_redirect_type
{
	is_input = 5,
	is_output,
	is_append,
	is_here_doc,
};

typedef struct s_global{
	t_env		*env;
	t_commands	*cmd_list;
	t_token		*token_list;
	char		**envp;
	int			operation;
	int			pipe;
	int			exit_status;
	int			stdin_backup;
	int			multiple_cmds;
	int			**fd;
}				t_global;

extern t_global	g_megabash;

#endif
