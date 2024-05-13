/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 18:08:18 by myokogaw          #+#    #+#             */
/*   Updated: 2024/04/23 18:08:18 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_right(t_ast *right)
{
	ft_free_matrix_char(right->cmd);
	free(right->path);
}

void	ft_free_ast(t_ast *root)
{
	if (root->esq)
		ft_free_ast(root->esq);
	if (root->dir)
	{
		free_right(root->dir);
		free(root->dir);
	}
	free(root);
}
