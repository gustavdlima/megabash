#include "minishell.h"

void	print_commands(t_commands *commands)
{
	if (!commands)
		return ;
	while (commands)
	{
		printf("command-> type: %d\n", commands->type);
		printf("command-> cmd: %s\n", commands->cmd);
		if (commands->content)
		{
			for (int j = 0; commands->content[j]; j++)
				printf("command-> content: %s\n", commands->content[j]);
		}
		while (commands->redirect)
		{
			printf("redirect-> type: %d\n", commands->redirect->type);
			printf("redirect-> file: %s\n", commands->redirect->content);
			commands->redirect = commands->redirect->next;
		}
		commands = commands->next;
	}
}

void	cmd_lst_addback(t_commands **lst, t_commands *new)
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
		free_matrix(temp->content);
		free(temp->cmd);
		if (temp->redirect)
			free_redirect(temp->redirect);
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
		element->redirect = NULL;
		return (element);
	}
	return (NULL);
}
