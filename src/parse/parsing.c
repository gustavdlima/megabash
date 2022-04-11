#include "minishell.h"

t_commands *take_command(t_token *token, t_commands *command)
{
	char *temp;
	char *cmd;

	cmd = ft_strdup("");
	while (token)
	{
		printf("OII DENTRO1\n");
		if (token->type == IS_BUILTIN || token->type == IS_CMD)
			{
			printf("ENTREI NO PRIMEIRO IF\n");
			command->cmd = ft_strdup(token->content);
			}
		printf("OII DENTRO2\n");
		if (token->type == IS_PARAMETER || token->type == IS_BUILTIN
			|| token->type == IS_CMD)
		{
			printf("ENTREI NO SEGUNDO IF\n");
			temp = ft_strjoin(cmd, token->content);
			cmd = ft_strdup(temp);
			free(temp);
			if ((token->next == NULL) || token->next->type == IS_PIPE)
			{
				printf("ENTREI NO TERCEIRO IF\n");
				command->content = ft_split(cmd, ' ');
				free(cmd);
			}
		}
		if (token->next == NULL || token->next->type == IS_PIPE)
			break;
		printf("OII DENTRO3\n");
		token = token->next;
		// printf("kkk\n");
	}
	// free(cmd);
	return (command);
}

void	parsing(void)
{
	t_token	*t_list;
	t_commands *c_list;

	t_list = g_megabash.token_list;
	c_list = NULL;
	while (t_list)
	{
		if (c_list == NULL)
		{
			printf("OII FORA DENTRO DO IF\n");
			c_list = take_command(t_list, cmd_lst_new());
			g_megabash.cmd_list = c_list;
		}
		printf("OII FORA\n");
		cmd_addback(&c_list, take_command(t_list, cmd_lst_new()));
		t_list = t_list->next;
	}
}

// criar um novo no da estrutura comando, definir o tipo do comando e seus argumentos, na parte de argumento eh soh colocar numa array de string;

// dependendo de quantos p;ipes tiver eu ja posso criar a lista de comandos e depois so mudo os valores das variaveis
