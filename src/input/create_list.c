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

void	create_list(void)
{
	char	*cmd;
	char	*temp;

	cmd = ft_strdup("");
	while (g_megabash.token_list)
	{
		temp = ft_strjoin(cmd, g_megabash.token_list->content);
		cmd = ft_strdup(temp);
		if (g_megabash.token_list->next)
			cmd = insert_caracter(cmd, ' ');
		g_megabash.token_list = g_megabash.token_list->next;
		free(temp);
	}
	printf("%s\n", cmd);
}
