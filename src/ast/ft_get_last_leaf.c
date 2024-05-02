/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_last_leaf.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:54:10 by myokogaw          #+#    #+#             */
/*   Updated: 2024/04/23 12:54:10 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*ft_get_last_leaf(t_ast *root, int direction)
{
	t_ast	*temp;

	if (!root)
		return (NULL);
	temp = root;
	if (direction == RIGHT)
		while (temp->right != NULL)
			temp = temp->right;
	else if (direction == LEFT)
		while (temp->left != NULL)
			temp = temp->left;
	return (temp);
}
