#include "minishell.h"

int	jump_positions(char *cmd, int position)
{
	char	*name;
	int		len;
	int		i;

	i = 0;
	while (cmd[i] || cmd[i] == ' ')
		i++;
	if (cmd[i] == '\0')
		return (i);
	position++;
	name = ft_substr(cmd, position, i);
	while (g_megabash.env)
	{
		len = ft_strlen(g_megabash.env->name) + 1;
		if(ft_strnstr(name, g_megabash.env->name, ft_strlen(name)) != NULL)
		{
			free (name);
			return (len);
		}
		g_megabash.env = g_megabash.env->next;
	}
	return (0);
}
