/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:55:41 by myokogaw          #+#    #+#             */
/*   Updated: 2024/05/01 18:53:19 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parser(t_dlist **tokens)
{
	t_ast	**root;

	if (parser_validation(tokens))
		return (2);
	root = ft_create_ast(tokens);
	execution(root);
	ft_free_ast(root);
	return (0);
}
