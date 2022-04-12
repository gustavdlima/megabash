#include "minishell.h"

void	print_commands(t_commands *commands)
{
	if (!commands)
		return ;
	while (commands)
	{
		printf("type: %d\n", commands->type);
		printf("cmd: %s\n", commands->cmd);
		for (int j = 0; commands->content[j]; j++)
			printf("content: %s\n", commands->content[j]);
		commands = commands->next;
	}
}

void	cmd_addback(t_commands **lst, t_commands *new)
{
	t_commands	*i;

	if (*lst)
	{
		i = cmd_last_node(*lst);
		i->next = new;
	}
	else
		*lst = new;
}

t_commands	*cmd_last_node(t_commands *lst)
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
	t_commands	*temp;

	while (commands)
	{
		temp = commands;
		commands = commands->next;
		free(temp->cmd);
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
		element->cmd = NULL;
		element->content = NULL;
		element->next = NULL;
		return (element);
	}
	return (0);
}
