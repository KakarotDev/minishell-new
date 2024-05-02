/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_ast.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:42:55 by myokogaw          #+#    #+#             */
/*   Updated: 2024/04/23 15:42:55 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	**ft_create_ast(t_dlist **tokens)
{
	t_ast	**root;
	t_dlist	*last_occur;

	root = (t_ast **) ft_calloc(1, sizeof(t_ast **));
	while (ft_dlist_have_type(tokens, PIPE))
	{
		last_occur = ft_dlist_last_occur(tokens, PIPE);
		ft_constructor_ast(root, last_occur);
		ft_dlist_delete_from(last_occur);
	}
	ft_ast_append_leaf(root,
		ft_ast_new_leaf(ft_cpy_dlst(*tokens), CMD), LEFT);
	ft_destructor_struct(tokens);
	return (root);
}
