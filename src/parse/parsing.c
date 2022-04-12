#include "minishell.h"

static void	treat_parse_list(void)
{
	t_commands	*temp;
	int			i;

	temp = g_megabash.cmd_list;
	i = 0;
	while (temp)
	{
		while (temp->content[i])
		{
			temp->content[i] = no_quotes(temp->content[i]);
			reverse_input_chars(temp->content[i]);
			i++;
		}
		temp = temp->next;
	}
}

t_commands	*take_command(t_token *token, t_commands *command)
{
	char	*temp;
	char	*cmd;

	cmd = ft_strdup("");
	while (token)
	{
		if (token->type == IS_BUILTIN || token->type == IS_CMD)
			command->cmd = ft_strdup(token->content);
		if (token->type == IS_PARAMETER || token->type == IS_BUILTIN
			|| token->type == IS_CMD)
		{
			temp = ft_strjoin(cmd, token->content);
			temp = insert_caracter(temp, ' ');
			cmd = ft_strdup(temp);
			free(temp);
			if ((token->next == NULL) || token->next->type == IS_PIPE)
				command->content = ft_split(cmd, ' ');
		}
		if (token->next == NULL || token->next->type == IS_PIPE)
			break ;
		token = token->next;
	}
	free(cmd);
	return (command);
}

t_token	*to_null_or_pipe(t_token *token)
{
	while (token)
	{
		if (token->next == NULL || token->next->type == IS_PIPE)
			break ;
		token = token->next;
	}
	return (token);
}

void	parsing(void)
{
	t_token		*t_list;
	t_commands	*c_list;

	t_list = g_megabash.token_list;
	c_list = NULL;
	while (t_list)
	{
		if (c_list == NULL)
		{
			c_list = take_command(t_list, cmd_lst_new());
			t_list = to_null_or_pipe(t_list);
			if (t_list->next == NULL || t_list->next->type == IS_PIPE)
				t_list = t_list->next;
			g_megabash.cmd_list = c_list;
			continue ;
		}
		cmd_addback(&c_list, take_command(t_list, cmd_lst_new()));
		t_list = to_null_or_pipe(t_list);
		t_list = t_list->next;
	}
	treat_parse_list();
}

/*
- criar um novo no da estrutura comando, definir o tipo do comando e seus
argumentos, na parte de argumento eh soh colocar numa array de string;

- dependendo de quantos pipes tiver eu ja posso criar a lista de comandos e
depois so mudo os valores das variaveis
*/
