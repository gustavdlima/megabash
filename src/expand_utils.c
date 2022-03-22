#include "minishell.h"

int	jump_positions(char *cmd)
{
	int		len;

	while (g_megabash.env)
	{
		len = ft_strlen(g_megabash.env->name) + 1;
		if(ft_strnstr(cmd, g_megabash.env->name, ft_strlen(cmd)) != NULL)
			return (len);
		g_megabash.env = g_megabash.env->next;
	}
	return (0);
}

