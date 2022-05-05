#include "minishell.h"

// static void	treat_parse_list(void)
// {
// 	t_commands	*temp;
// 	int			i;

// 	temp = g_megabash.cmd_list;
// 	i = 0;
// 	while (temp)
// 	{
// 		while (temp->content[i])
// 		{
// 			temp->content[i] = no_quotes(temp->content[i]);
// 			reverse_input_chars(temp->content[i]);
// 			i++;
// 		}
// 		temp = temp->next;
// 	}
// }

// t_token	*to_null_or_pipe(t_token *token)
// {
// 	while (token)
// 	{
// 		if (token->next == NULL || token->next->type == is_pipe)
// 			break ;
// 		token = token->next;
// 	}
// 	return (token);
// }

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

// static t_token *cmd_redirect_parse(t_token *token, t_redirect *redirect)
// {
// 	char	*temp;

// 	redirect->type = redirect_type(token->content);
// 	token = token->next;
// 	redirect->content = ft_strdup("");
// 	while (token)
// 	{
// 		if (redirect->type == is_input)
// 		{
// 			if (token->type == is_word)
// 				return (token);
// 			if (token->type == is_word)
// 			{
// 				temp = ft_strjoin(redirect->content, token->content);
// 				redirect->content = ft_strdup(temp);
// 				redirect->content = insert_caracter(redirect->content, ' ');
// 				free(temp);
// 			}
// 			if (token->type == is_redirect)
// 				return (token);
// 		}
// 		token = token->next;
// 	}
// 	return (token);
// }

// static t_token *cmd_parse(t_token *token, t_commands *command)
// {
// 	char		*temp;
// 	char		*cmd_string;

// 	command->cmd = ft_strdup(token->content);
// 	token = token->next;
// 	cmd_string = ft_strdup(command->cmd);
// 	command->redirect = NULL;
// 	while (token)
// 	{
// 		if (token->type == is_pipe)
// 			return (token);
// 		if (token->type == is_word)
// 		{
// 			cmd_string = insert_caracter(cmd_string, ' ');
// 			temp = ft_strjoin(cmd_string, token->content);
// 			cmd_string = ft_strdup(temp);
// 			free(temp);
// 		}
// 		if (token->type == is_redirect)
// 		{
// 			if (!command->redirect)
// 			{
// 				command->redirect = redirect_lst_new();
// 				token = cmd_redirect_parse(token, command->redirect);
// 			}
// 			else
// 			{

// 				token = cmd_redirect_parse(token, redirect_addback(&command->redirect, redirect_lst_new()));
// 			}
// 			continue ;
// 		}
// 		token = token->next;
// 	}
// 	// tenho que verificar se no ultimo espaco da split eh null ou espaco
// 	command->content = ft_split(cmd_string, ' ');
// 	// printf("command->cmd = %s\n", command->cmd);
// 	// printf("command->content: ");
// 	// for (int p = 0; command->content[p]; p++)
// 	// 	printf("%s ", command->content[p]);
// 	// printf("\n");
// 	print_commands(command);
// 	return (token);
// }

//  // < file tr 'a' 'b'
// //  > file cat Makefile
// static t_token *redirect_cmd_parse(t_token *token, t_redirect *redirect)
// {
// 	char	*temp;

// 	redirect->type = redirect_type(token->content);
// 	token = token->next;
// 	redirect->content = ft_strdup("");
// 	while (token)
// 	{
// 		if (token->type == is_word && token->prev->type == is_word)
// 			return (token);
// 		if (token->type == is_word)
// 		{
// 			temp = ft_strjoin(redirect->content, token->content);
// 			redirect->content = ft_strdup(temp);
// 			redirect->content = insert_caracter(redirect->content, ' ');
// 			free(temp);
// 		}
// 		if (token->type == is_redirect)
// 			return (token);
// 		token = token->next;
// 	}
// 	return (token);
// }
//  // < file tr 'a' 'b'
// //  > file cat Makefile
// static t_token *redirect_parse(t_token *token, t_commands *command)
// {
// 	command->redirect = NULL;
// 	while (token)
// 	{
// 		if (token->type == is_redirect)
// 		{
// 			if (command->redirect == NULL)
// 			{
// 				command->redirect = redirect_lst_new();
// 				token = redirect_cmd_parse(token, command->redirect);
// 			}
// 			else
// 			{
// 				token = redirect_cmd_parse(token, redirect_addback(&command->redirect, redirect_lst_new()));
// 			}
// 			continue ;
// 		}
// 		if (token->type == is_word)
// 			return (token);
// 		token = token->next;
// 	}
// 	return (token);
// }
// < file tr 'a' 'b'
// > file cat Makefile

static t_token *cmd_parse(t_token *token, t_commands *command)
{
	char		*temp;
	char		*cmd_string;

	command->cmd = ft_strdup(token->content);
	token = token->next;
	cmd_string = ft_strdup(command->cmd);
	command->redirect = NULL;
	while (token)
	{
		if (token->type == is_pipe)
			return (token);
		if (token->type == is_word)
		{
			cmd_string = insert_caracter(cmd_string, ' ');
			temp = ft_strjoin(cmd_string, token->content);
			cmd_string = ft_strdup(temp);
			free(temp);
		}
		if (token->type == is_redirect)
			return (token);
		token = token->next;
	}
	command->content = ft_split(cmd_string, ' ');
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
			temp = ft_strjoin(redirect->content, token->content);
			redirect->content = ft_strdup(temp);
			redirect->content = insert_caracter(redirect->content, ' ');
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
			if (command->redirect == NULL)
			{
				command->redirect = redirect_lst_new();
				token = redirect_parse(token, command->redirect);
				continue;
			}
			else
			{
				token = redirect_parse(token, redirect_addback(&command->redirect, redirect_lst_new()));
				continue;
			}
		}
		token = token->next;
	}
	return (token);
}

void parsing(void)
{
	t_token *token;

	token = g_megabash.token_list;
	g_megabash.cmd_list = NULL;
	while (token)
	{
		if (g_megabash.cmd_list == NULL)
		{
			g_megabash.cmd_list = cmd_lst_new();
			token = parsing_check(token, g_megabash.cmd_list);
			continue;
		}
		else
		{
			cmd_lst_addback(&g_megabash.cmd_list, cmd_lst_new());
			token = parsing_check(token, g_megabash.cmd_list);
			continue;
		}
		token = token->next;
	}
	print_commands(g_megabash.cmd_list);
	// treat_parse_list();
}
