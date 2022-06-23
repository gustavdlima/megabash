#include "minishell.h"

int	execute_builtin(t_commands *cmd_list)
{
	if (!ft_strncmp(cmd_list->cmd, "cd", 3))
	{
		cd(cmd_list->content);
		return (true);
	}
	if (!ft_strncmp(cmd_list->cmd, "env", 4))
	{
		builtin_env(cmd_list->content);
		return (true);
	}
	if (!ft_strncmp(cmd_list->cmd, "echo", 5))
	{
		echo(cmd_list->content);
		return (true);
	}
	if (!ft_strncmp(cmd_list->cmd, "unset", 6))
	{
		unset(cmd_list->content);
		return (true);
	}
	if (!ft_strncmp(cmd_list->cmd, "export", 7))
	{
		export(cmd_list->content);
		return (true);
	}
	if (!ft_strncmp(cmd_list->cmd, "exit", 5))
	{
		b_exit(cmd_list->content);
		exit(g_megabash.exit_status);
	}
	if (!ft_strncmp(cmd_list->cmd, "pwd", 3))
	{
		pwd(cmd_list->content);
		return (true);
	}
	return (false);
}
