/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalves <gusalves@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 21:06:00 by gusalves          #+#    #+#             */
/*   Updated: 2022/07/16 00:39:43 by gusalves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINKED_LIST_H
# define LINKED_LIST_H

# include "minishell.h"

t_env		*env_lst_new(char *name, char *content);
int			env_name_check(t_env *lst, char *name);
void		env_addback(t_env **lst, t_env *new);
t_env		*env_last_node(t_env *lst);
int			env_lst_size(t_env *lst);

#endif
