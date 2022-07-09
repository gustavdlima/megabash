#include "minishell.h"

static int	redirect_type(char *content)
{
	if (!ft_strncmp(content, ">", 2))
		return (is_output);
	else if (!ft_strncmp(content, "<", 2))
		return (is_input);
	else if (!ft_strncmp(content, ">>", 3))
		return (is_append);
	else if (!ft_strncmp(content, "<<", 3))
		return (is_here_doc);
	else
		return (false);
}

static	char *cmd_operation(char *cmd_string, char *token_content)
{
	char *temp;

	cmd_string = insert_caracter(cmd_string, ' ');
	temp = ft_strjoin(cmd_string, token_content);
	free(cmd_string);
	cmd_string = ft_strdup(temp);
	free(temp);
	return (cmd_string);
}

static t_commands	*copy_string_to_inside_matrix(t_commands *cmd_list, char *string)
{
	int	i;
	char	*temp;
	char	*new_string;

	i = 0;
	new_string = ft_strdup("");
	while(cmd_list->content[i])
	{
		temp = ft_strjoin(new_string, cmd_list->content[i]);
		free(new_string);
		new_string = ft_strdup(temp);
		new_string = insert_caracter(new_string, ' ');
		free(temp);
		i++;
	}
	new_string = insert_caracter(new_string, ' ');
	temp = ft_strjoin(new_string, string);
	free_matrix(cmd_list->content);
	cmd_list->content = ft_split(temp, ' ');
	free(new_string);
	free(temp);
	return (cmd_list);
}

static t_token *cmd_parse_loop(t_token *token, t_commands *command, char *cmd_string)
{
	t_token	*token_temp;

	while (token)
	{
		if (token->type == is_pipe)
		{
			command->content = ft_split(cmd_string, ' ');
			free (cmd_string);
			return (token);
		}
		if (token->type == is_redirect)
		{
			if (token->next->next && token->next->next->type == is_word)
			{
				token_temp = token->next->next;
				while (token_temp->type == is_word)
				{
					cmd_string = cmd_operation(cmd_string, token_temp->content);
					token = token_content_to_hell(token, token_temp->content,
							token->content);
					if(token->next)
						token_temp = token->next;
					if (token_temp->next)
						token_temp = token_temp->next;
					else
						break ;
				}
			}
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

static t_token	*cmd_parse(t_token *token, t_commands *command)
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

static t_token	*redirect_parse(t_token *token, t_redirect *redirect)
{
	char	*temp;

	redirect->type = redirect_type(token->content);
	token = token->next;
	redirect->content = ft_strdup("");
	while (token)
	{
		if (token->type == is_pipe)
			return (token);
		if (token->type == is_word && token->prev->type == is_word)
			return (token);
		if (token->type == is_word)
		{
			temp = ft_strjoin(redirect->content, token->content);
			free(redirect->content);
			redirect->content = ft_strdup(temp);
			free(temp);
		}
		if (token->type == is_redirect)
			return (token);
		token = token->next;
	}
	return (token);
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
	// print_commands(cmd_temp);
	treat_parse_list();
}
