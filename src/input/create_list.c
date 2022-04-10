#include "minishell.h"

char	*insert_caracter(char *cmd, char caracter)
{
	int	i;
	char *new_cmd;

	new_cmd = malloc(sizeof(char) * (ft_strlen(cmd) + 2));
	i = 0;
	while(cmd[i])
	{
		new_cmd[i] = cmd[i];
		i++;
	}
	new_cmd[i] = caracter;
	i++;
	new_cmd[i] = '\0';
	free(cmd);
	return (new_cmd);
}

int	check_operator(char operator)
{
	if (operator == '|')
			return (TRUE);
	else if	(operator == '>')
			return (TRUE);
	else if	(operator == '<')
			return (TRUE);
	else
		return (FALSE);
}

int	is_operator(char *input)
{
	if (!ft_strncmp(input, "|", 2))
			return (IS_PIPE);
	else if	(!ft_strncmp(input, ">", 2))
			return (IS_REDIRECT);
	else if	(!ft_strncmp(input, "<", 2))
			return (IS_REDIRECT);
	else if	(!ft_strncmp(input, ">>", 3))
			return (IS_REDIRECT);
	else if	(!ft_strncmp(input, "<<", 3))
			return (IS_HERE_DOC);
	else
		return (FALSE);
}

static void create_list_pipe(void)
{
	char *temp;
	char *cmd;

	cmd = ft_strdup("");
	while (g_megabash.token_list)
	{
		if (!ft_strncmp(g_megabash.token_list->content, "|", 2))
		{
			g_megabash.pipe++;
			if (!g_megabash.cmd_list)
				g_megabash.cmd_list = cmd_lst_new_args(cmd);
			else
				commands_addback(&g_megabash.cmd_list, cmd_lst_new_args(cmd));
			g_megabash.token_list = g_megabash.token_list->next;
			free(cmd);
		}
		temp = ft_strjoin(cmd, g_megabash.token_list->content);
		cmd = ft_strdup(temp);
		if (g_megabash.token_list->next)
			cmd = insert_caracter(cmd, ' ');
		g_megabash.token_list = g_megabash.token_list->next;
		free(temp);
	}
}

void	create_list(void)
{
	char	*cmd;
	char	*temp;

	cmd = ft_strdup("");
	while (g_megabash.token_list)
	{
		if (token_caracter_checker(g_megabash.token_list, "|"))
			create_list_pipe();
		else
		{
			if (g_megabash.token_list->next)
				cmd = insert_caracter(cmd, ' ');
			else
			{
				if (!g_megabash.cmd_list)
					g_megabash.cmd_list = cmd_lst_new_args(cmd);
				else
					commands_addback(&g_megabash.cmd_list, cmd_lst_new_args(cmd));
			}
			// o fim do comando nao ta entrando aqui pq entra no else acima
			temp = ft_strjoin(cmd, g_megabash.token_list->content);
			cmd = ft_strdup(temp);
			g_megabash.token_list = g_megabash.token_list->next;
			free(temp);
		}
	}
}
