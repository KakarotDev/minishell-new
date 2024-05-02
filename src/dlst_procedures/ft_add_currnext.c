/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_currnext.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 18:21:38 by myokogaw          #+#    #+#             */
/*   Updated: 2024/05/02 16:53:51 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_dlist	*ft_add_currnext(t_dlist *token, t_dlist *new_token, int iteration)
{
	t_dlist	*next;

	if (!iteration)
	{
		free(token->tok->lex);
		token->tok->lex = ft_strdup(new_token->tok->lex);
		token->tok->type = new_token->tok->type;
		ft_cpy_array_data(token->tok->data, new_token->tok->data, 3);
		free_struct_token(new_token->tok);
		free(new_token);
		return (token);
	}
	if (token->next)
	{
		next = token->next;
		next->prev = new_token;
	}
	else
		next = NULL;
	token->next = new_token;
	new_token->prev = token;
	new_token->next = next;
	return (new_token);
}
