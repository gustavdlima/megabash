#include "minishell.h"

void	insert_caracter(char **cmd, char caracter)
{
	*cmd = ft_strdup(*cmd + 1);
	*cmd[ft_strlen(*cmd) - 1] = caracter;
}

int	is_operator(char *input)
{
	if (!ft_strncmp(input, "|", 2))
			return (TRUE);
	else if	(!ft_strncmp(input, ">", 2))
			return (TRUE);
	else if	(!ft_strncmp(input, "<", 2))
			return (TRUE);
	else if	(!ft_strncmp(input, ">>", 3))
			return (TRUE);
	else if	(!ft_strncmp(input, "<<", 3))
			return (TRUE);
	else
		return (FALSE);
}

void	create_list(void)
{
	char	*cmd;
	char	*temp;

	cmd = ft_strdup("");
	g_megabash.cmd_list = cmd_lst_new();
	while (g_megabash.token_list)
	{
		if (!ft_strncmp(g_megabash.token_list->content, "|", 2))
		{
			commands_addback(&g_megabash.cmd_list, cmd_lst_new_args(cmd, 0)); //TESTANDO
			free(cmd);
			g_megabash.pipe++;
			g_megabash.token_list = g_megabash.token_list->next;
		}
		printf("OIII\n");
		temp = ft_strjoin(cmd, g_megabash.token_list->content);
		// insert_caracter(&cmd, ' ');
		cmd = ft_strdup(temp);
		free(temp);
		g_megabash.token_list = g_megabash.token_list->next;
	}
}
