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

// t_commands	*take_command(t_token *token, t_commands *command)
// {

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

int	redirect_type(char *content)
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

t_token *redirect_parse(t_token *token, struct s_redirect *redirect)
{
	char	*temp;

	redirect->type = redirect_type(token->content);
	token = token->next;
	redirect->content = ft_strdup("");
	while (token)
	{
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

t_token *command_parse(t_token *token, t_commands *command)
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
		{
			if (!command->redirect)
			{
				command->redirect = redirect_lst_new();
				token = redirect_parse(token, command->redirect);
			}
			else
				token = redirect_parse(token, redirect_addback(&command->redirect, redirect_lst_new()));
			continue ;
		}
		token = token->next;
	}
	// tenho que verificar se no ultimo espaco da split eh null ou espaco
	command->content = ft_split(cmd_string, ' ');
	printf("command->cmd = %s\n", command->cmd);
	printf("command->content: ");
	for (int p = 0; command->content[p]; p++)
		printf("%s ", command->content[p]);
	printf("\n");
	print_redirect(command->redirect);
	return (token);
}

// ls > file
// < file ls > file
// file1 > file2 > file3 cat Makefile > file4

void	parsing(void)
{
	t_token		*token;

	token = g_megabash.token_list;
	while (token)
	{
		if (token->type == is_word)
		{
        	token = command_parse(token, cmd_lst_new());
			continue ;
		}
        if (token->type == is_pipe)
			g_megabash.pipe++;
		if (token->type == is_redirect || token->type == is_here_doc)
			printf ("comecamos com redirect ou here-doc\n");
		token = token->next;
	}
	// treat_parse_list();
}
