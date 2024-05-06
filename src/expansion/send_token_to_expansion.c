/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_token_to_expansion.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 19:30:16 by myokogaw          #+#    #+#             */
/*   Updated: 2024/05/06 15:21:28 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	send_token_to_expansion(t_dlist **tokens, char **environment)
{
	t_dlist	*token;

	token = *tokens;
	while (token)
	{
		if (token->tok->type == ASSIGNMENT_WORD)
			var_expansion(token, environment);
		else if (token->next == NULL)
			break ;
		else
			token = token->next;
	}
	return ;
}
