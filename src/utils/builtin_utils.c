#include "minishell.h"

int	execute_builtin(void)
{
	if (!ft_strncmp(g_megabash.cmd_list->cmd, "cd", 3))
	{
		cd(g_megabash.cmd_list->content);
		return (true);
	}
	if (!ft_strncmp(g_megabash.cmd_list->cmd, "env", 4))
	{
		builtin_env(g_megabash.cmd_list->content);
		return (true);
	}
	if (!ft_strncmp(g_megabash.cmd_list->cmd, "echo", 5))
	{
		echo(g_megabash.cmd_list->content);
		return (true);
	}
	if (!ft_strncmp(g_megabash.cmd_list->cmd, "unset", 6))
	{
		unset(g_megabash.cmd_list->content);
		return (true);
	}
	if (!ft_strncmp(g_megabash.cmd_list->cmd, "export", 7))
	{
		export(g_megabash.cmd_list->content);
		return (true);
	}
	if (!ft_strncmp(g_megabash.cmd_list->cmd, "exit", 5))
	{
		b_exit(g_megabash.cmd_list->content);
		return (true);
	}
	return (false);
}
