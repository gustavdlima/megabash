#include "minishell.h"

void	execute_builtin(t_commands *cmd_list)
{
	if (!cmd_list->cmd)
		return ;
	if (!ft_strncmp(cmd_list->cmd, "cd", 3))
		cd(cmd_list->content);
	if (!ft_strncmp(cmd_list->cmd, "env", 4))
		builtin_env(cmd_list->content);
	if (!ft_strncmp(cmd_list->cmd, "echo", 5))
		echo(cmd_list->content);
	if (!ft_strncmp(cmd_list->cmd, "unset", 6))
		unset(cmd_list->content);
	if (!ft_strncmp(cmd_list->cmd, "export", 7))
		export(cmd_list->content);
	if (!ft_strncmp(cmd_list->cmd, "exit", 5))
		builtin_exit(cmd_list->content);
	if (!ft_strncmp(cmd_list->cmd, "pwd", 3))
		pwd(cmd_list->content);
}
