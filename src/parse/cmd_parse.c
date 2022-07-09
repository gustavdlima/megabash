#include "minishell.h"

static t_token	*connect_cmd_to_late_args(t_token *token, char *cmd_string)
{
	t_token	*token_temp;

	token_temp = token->next->next;
	while (token_temp->type == is_word)
	{
		cmd_string = cmd_operation(cmd_string, token_temp->content);
		token = token_content_to_hell(token, token_temp->content,
				token->content);
		if (token->next)
			token_temp = token->next;
		if (token_temp->next)
			token_temp = token_temp->next;
		else
			break ;
	}
	return (token);
}

static t_token	*cmd_parse_loop(t_token *token, t_commands *command,
					char *cmd_string)
{
	while (token)
	{
		if (token->type == is_pipe)
			break ;
		if (token->type == is_redirect)
		{
			if (token->next->next && token->next->next->type == is_word)
				token = connect_cmd_to_late_args(token, cmd_string);
			command->content = ft_split(cmd_string, ' ');
			free (cmd_string);
			return (token);
		}
		if (token->type == is_word)
			cmd_string = cmd_operation(cmd_string, token->content);
		token = token->next;
	}
	if (command->redirect && command->content[0])
		command = copy_string_to_inside_matrix(command, cmd_string);
	else
		command->content = ft_split(cmd_string, ' ');
	free(cmd_string);
	return (token);
}

t_token	*cmd_parse(t_token *token, t_commands *command)
{
	char		*cmd_string;

	if (!command->cmd)
	{
		command->cmd = ft_strdup(token->content);
		cmd_string = ft_strdup(command->cmd);
	}
	else
		cmd_string = ft_strdup(token->content);
	token = token->next;
	token = cmd_parse_loop(token, command, cmd_string);
	return (token);
}
