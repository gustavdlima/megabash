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
// 		if (token->next == NULL || token->next->type == IS_PIPE)
// 			break ;
// 		token = token->next;
// 	}
// 	return (token);
// }

// primeiro passo, testar com um comando normal

t_token *command_parse(t_token *token, t_commands *command)
{
	char	*temp;
	char	*cmd_string;

	command->cmd = ft_strdup(token->content);
	token = token->next;
	cmd_string = ft_strdup(command->cmd);
	while (token)
	{
		if (token->type == IS_PIPE)
			return (token);
		if (token->type == IS_WORD && (token->prev->type != IS_REDIRECT
			|| token->prev->type != IS_HERE_DOC))
		{
			cmd_string = insert_caracter(cmd_string, ' ');
			temp = ft_strjoin(cmd_string, token->content);
			cmd_string = ft_strdup(temp);			free(temp);
		}
		if (token->type == IS_REDIRECT || token->type == IS_HERE_DOC)
		{	
			printf ("era pra ter um redirect aqui\n");
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
		if (token->type == IS_WORD)
		{
        	token = command_parse(token, cmd_lst_new());
			continue ;
		}
        if (token->type == IS_PIPE)
			g_megabash.pipe++;
		if (token->type == IS_REDIRECT || token->type == IS_HERE_DOC)
			printf ("comecamos com redirect ou here-doc\n");
		token = token->next;
	}
    // print_commands(command);
	// treat_parse_list();
}
