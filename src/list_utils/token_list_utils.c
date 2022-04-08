#include "minishell.h"

void	print_token(t_token *token)
{
	if (!token)
		return ;
	while(token)
	{
		printf("Token content: %s\n", token->content);
		token = token->next;
	}
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
