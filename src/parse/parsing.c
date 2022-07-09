#include "minishell.h"

static void	treat_parse_list(void)
{
	t_commands	*cmd_temp;
	int			i;

	cmd_temp = g_megabash.cmd_list;
	while (cmd_temp)
	{
		i = 0;
		if (cmd_temp->content)
		{
			while (cmd_temp->content[i])
			{
				cmd_temp->content[i] = no_quotes(cmd_temp->content[i]);
				reverse_input_chars(cmd_temp->content[i]);
				i++;
			}
		}
		cmd_temp = cmd_temp->next;
	}
}

static t_token	*parsing_check(t_token *token, t_commands *command)
{
	while (token)
	{
		if (token->type == is_word)
		{
			token = cmd_parse(token, command);
			continue ;
		}
		else if (token->type == is_pipe)
		{
			g_megabash.pipe++;
			token = token->next;
			return (token);
		}
		else if (token->type == is_redirect)
		{
			redirect_addback(&command->redirect, redirect_lst_new());
			token = redirect_parse(token,
					redirect_last_node(command->redirect));
			continue ;
		}
		token = token->next;
	}
	return (token);
}

void	parsing(void)
{
	t_commands	*cmd_temp;
	t_token		*token;

	token = g_megabash.token_list;
	cmd_temp = NULL;
	while (token)
	{
		cmd_lst_addback(&cmd_temp, cmd_lst_new());
		token = parsing_check(token, cmd_last_node(cmd_temp));
		continue ;
	}
	g_megabash.cmd_list = cmd_temp;
	treat_parse_list();
}
