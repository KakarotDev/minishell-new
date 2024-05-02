/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_validation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 22:40:50 by myokogaw          #+#    #+#             */
/*   Updated: 2024/04/29 22:40:50 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parser_validation(t_dlist **tokens)
{
	if (!*tokens)
	{
		ft_destructor_struct(tokens);
		return (0);
	}
	if (check_pipes(tokens))
		return (syntax_error(UNEXPECTED, tokens, NULL));
	else if (check_redirections(tokens))
		return (syntax_error(UNEXPECTED, tokens, NULL));
	return (0);
}
