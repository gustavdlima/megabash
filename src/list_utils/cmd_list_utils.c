#include "minishell.h"

void	print_commands(t_commands *commands)
{
	if (!commands)
		return ;
	while(commands)
	{
		printf("Commands content: %s\n", commands->cmd);
		commands = commands->next;
	}
}

void	commands_addback(t_commands **lst, t_commands *new)
{
	t_commands	*i;
	if (*lst)
	{
		i = commands_last_node(*lst);
		i->next = new;
	}
	else
		*lst = new;
}

t_commands	*commands_last_node(t_commands *lst)
{
	if (lst)
	{
		while (lst->next != NULL)
			lst = lst->next;
		return (lst);
	}
	return (NULL);
}

void	free_commands(t_commands *commands)
{
	t_commands *temp;

	while (commands)
	{
		temp = commands;
		commands = commands->next;
		free(temp->cmd);
		free_matrix(temp->cmd_matrix);
		free(temp);
	}
}

t_commands	*cmd_lst_new(void)
{
	t_commands	*element;

	element = malloc(sizeof(t_commands));
	if (element)
	{
		element->type = 0;
		element->cmd_matrix = NULL;
		element->cmd = NULL;
		element->next = NULL;
		return (element);
	}
	return (0);
}

t_commands	*cmd_lst_new_args(char *cmd, int type)
{
	t_commands	*element;

	element = malloc(sizeof(t_commands));
	if (element)
	{
		element->type = type;
		element->cmd_matrix = ft_split(cmd, ' ');
		element->cmd = ft_strdup(cmd);
		element->next = NULL;
		return (element);
	}
	return (0);
}
