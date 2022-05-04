#include "minishell.h"

void    set_token_type(t_token *list)
{
    while (list)
    {
        if (!list->content)
            return ;
        if (check_operator(list->content[0]))
        {
            list->type = is_operator(list->content);
            printf("tipo: %d\n", list->type);
        }
        else
        {
            list->type = is_word;
            printf("tipo: %d\n", list->type);
        }
        list = list->next;
    }
}
