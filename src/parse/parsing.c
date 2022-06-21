#include "minishell.h"

static int redirect_type(char *content)
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

static t_token *cmd_parse(t_token *token, t_commands *command)
{
	char		*temp;
	char		*cmd_string;

	command->cmd = ft_strdup(token->content);
	token = token->next;
	cmd_string = ft_strdup(command->cmd);
	while (token)
	{
		if (token->type == is_pipe || token->type == is_redirect)
		{
			command->content = ft_split(cmd_string, ' ');
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

static t_token *redirect_parse(t_token *token, t_redirect *redirect)
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
			printf("oi to parseando a file\n");
			temp = ft_strjoin(redirect->content, token->content);
			redirect->content = ft_strdup(temp);
			redirect->content = insert_caracter(redirect->content, ' ');
			printf ("file >>> %s\n", redirect->content);
			free(temp);
		}
		if (token->type == is_redirect)
			return (token);
		token = token->next;
	}
	return (token);
}

static t_token *parsing_check(t_token *token, t_commands *command)
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
				token = redirect_parse(token, redirect_last_node(command->redirect));
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
			printf("command no treated: %s\n", cmd_temp->content[i]);
			cmd_temp->content[i] = no_quotes(cmd_temp->content[i]);
			reverse_input_chars(cmd_temp->content[i]);
			printf("command treated: %s\n", cmd_temp->content[i]);
			i++;
		}
		cmd_temp = cmd_temp->next;
	}
}

void	parsing(void)
{
	t_token	*token;
	t_commands	*cmd_temp;

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
