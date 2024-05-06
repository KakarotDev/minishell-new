/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_constructor_ast.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 17:00:04 by myokogaw          #+#    #+#             */
/*   Updated: 2024/05/05 19:46:33 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_constructor_ast(t_ast **root, t_dlist *last_occur)
{
	t_ast	*last_leaf_left;

	if (!*root)
	{
		*root = ft_ast_new_leaf(NULL, PIPE);
		last_leaf_left = *root;
		last_leaf_left->right = ft_ast_new_leaf(
				ft_cpy_dlst(last_occur->next), CMD);
		return ;
	}
	ft_ast_append_leaf(root, ft_ast_new_leaf(NULL, PIPE), LEFT);
	last_leaf_left = ft_get_last_leaf(*root, LEFT);
	last_leaf_left->right = ft_ast_new_leaf(
			ft_cpy_dlst(last_occur->next), CMD);
	return ;
}
