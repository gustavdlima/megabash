#include "minishell.h"

void	print_token(t_token *token)
{
	if (!token)
		return ;
	printf("\nToken content: ------------\n");
	while(token)
	{
		printf("%s\n", token->content);
		token = token->next;
	}
	printf("---------------------------\n");
}

int token_pipe_checker(t_token *token)
{
	t_token	*list;

	list = token;
	while (list)
	{
		if (list->type == IS_PIPE)
			return (TRUE);
		list = list->next;
	}
	return (FALSE);
}

t_token	*token_lst_new(char *content)
{
	t_token	*element;

	element = malloc(sizeof(t_token));
	if (element)
	{
		element->type = 0;
		element->content = content;
		element->next = NULL;
		return (element);
	}
	return (0);
}

void	token_addback(t_token **lst, t_token *new)
{
	t_token	*i;
	if (*lst)
	{
		i = token_last_node(*lst);
		i->next = new;
	}
	else
		*lst = new;
}

t_token	*token_last_node(t_token *lst)
{
	if (lst)
	{
		while (lst->next != NULL)
			lst = lst->next;
		return (lst);
	}
	return (NULL);
}

void	free_token(t_token *token)
{
	t_token *temp;

	while (token)
	{
		temp = token;
		token = token->next;
		free(temp->content);
		free(temp);
	}
}
