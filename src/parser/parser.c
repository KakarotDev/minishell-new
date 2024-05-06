/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:55:41 by myokogaw          #+#    #+#             */
/*   Updated: 2024/05/05 19:47:45 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parser(t_dlist **tokens)
{
	t_ast	**root;

	if (last_exit_status(parser_validation(tokens)))
		return ;
	root = ft_create_ast(tokens);
	execution(root);
	ft_free_ast(root);
	return ;
}
