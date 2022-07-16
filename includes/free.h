/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalves <gusalves@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 21:05:52 by gusalves          #+#    #+#             */
/*   Updated: 2022/07/15 21:05:52 by gusalves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FREE_H
# define FREE_H

# include "minishell.h"

void	free_matrix(char **matrix);
void	free_int_matrix(int **matrix);
void	free_env(t_env *env);
void	free_cmd_megabash(void);
void	child_builtins_free_and_exit(int exit_status);

#endif
