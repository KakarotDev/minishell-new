/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 19:30:16 by myokogaw          #+#    #+#             */
/*   Updated: 2024/05/02 17:19:02 by myokogaw         ###   ########.fr       */
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
		if (token->next == NULL)
			return ;
		token = token->next;
	}
	return ;
}
