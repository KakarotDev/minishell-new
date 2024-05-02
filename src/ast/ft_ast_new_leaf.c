/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ast_new_leaf.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:48:13 by myokogaw          #+#    #+#             */
/*   Updated: 2024/04/23 12:48:13 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*ft_ast_new_leaf(t_dlist **exec_tokens, enum e_type type)
{
	t_ast	*new_leaf;

	new_leaf = (t_ast *) ft_calloc(1, sizeof(t_ast));
	new_leaf->exec_tokens = exec_tokens;
	new_leaf->type = type;
	new_leaf->size = ft_count_tokens(exec_tokens);
	return (new_leaf);
}
