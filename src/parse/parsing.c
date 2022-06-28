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

static t_token	*cmd_parse(t_token *token, t_commands *command)
{
	char		*temp;
	char		*cmd_string;
	t_token		*token_temp;

	command->cmd = ft_strdup(token->content);
	token = token->next;
	cmd_string = ft_strdup(command->cmd);
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
					cmd_string = insert_caracter(cmd_string, ' ');
					temp = ft_strjoin(cmd_string, token_temp->content);
					cmd_string = ft_strdup(temp);
					token = token_content_to_hell(token, token_temp->content,
							token->content);
					free(temp);
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
		{
			cmd_string = insert_caracter(cmd_string, ' ');
			temp = ft_strjoin(cmd_string, token->content);
			cmd_string = ft_strdup(temp);
			free(temp);
		}
		token = token->next;
	}
	command->content = ft_split(cmd_string, ' ');
	free(cmd_string);
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
			// printf("CONTEUDO REDIRECT : %s\n", command->redirect->content);
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
		while (cmd_temp->content[i])
		{
			// printf("command no treated: %s\n", cmd_temp->content[i]);
			cmd_temp->content[i] = no_quotes(cmd_temp->content[i]);
			reverse_input_chars(cmd_temp->content[i]);
			// printf("command treated: %s\n", cmd_temp->content[i]);
			i++;
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
	// print_commands(g_megabash.cmd_list);
	treat_parse_list();
}
