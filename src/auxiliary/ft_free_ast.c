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

void	ft_free_ast(t_ast **root)
{
	t_ast	*temp;
	t_ast	*temp1;

	if (!root)
		return ;
	if (!*root)
		return ;
	temp = *root;
	while (temp)
	{
		temp1 = temp;
		temp = temp1->left;
		if (temp == NULL)
			break ;
		ft_destructor_struct(temp1->right->exec_tokens);
		free(temp1->right);
		free(temp1);
	}
	ft_destructor_struct(temp1->exec_tokens);
	free(temp1);
	free(root);
	return ;
}
