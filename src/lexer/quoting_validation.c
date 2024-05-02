/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoting_validation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 20:06:29 by myokogaw          #+#    #+#             */
/*   Updated: 2024/03/26 20:06:29 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quoting_validation(char *input)
{
	int	s_quote;
	int	d_quote;

	s_quote = 0;
	d_quote = 0;
	while (*input)
	{
		if (*input == '\'' && s_quote == 0 && d_quote == 0)
			s_quote = 1;
		else if (*input == '\'' && s_quote == 1)
			s_quote = 0;
		if (*input == '\"' && d_quote == 0 && s_quote == 0)
			d_quote = 1;
		else if (*input == '\"' && d_quote == 1)
			d_quote = 0;
		input++;
	}
	if (s_quote == 1 || d_quote == 1)
		return (2);
	return (0);
}
