/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ast_append_leaf.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:47:38 by myokogaw          #+#    #+#             */
/*   Updated: 2024/04/23 12:47:38 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_ast_append_leaf(t_ast **root, t_ast *new_leaf, int side)
{
	t_ast	*temp;

	if (!root)
		return ;
	if (!*root)
	{
		*root = new_leaf;
		return ;
	}
	if (side == RIGHT)
	{
		temp = ft_get_last_leaf(*root, side);
		temp->right = new_leaf;
	}
	else if (side == LEFT)
	{
		temp = ft_get_last_leaf(*root, side);
		temp->left = new_leaf;
	}
	return ;
}
