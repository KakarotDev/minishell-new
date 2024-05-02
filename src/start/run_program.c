/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_program.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 17:01:47 by myokogaw          #+#    #+#             */
/*   Updated: 2024/05/02 18:40:28 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_program(void)
{
	t_dlist	**tokens;
	char	*input;

	hook_environ(copy_environ(), 0);
	handle_signal();
	while (TRUE)
	{
		input = readline("minishell: ");
		add_history(input);
		if (input == NULL)
			return (interrupt_program(input));
		if (quoting_validation(input))
			last_exit_status(syntax_error(UNCLOSED_QUOTE, NULL, input));
		else
		{
			tokens = lexer(input);
			last_exit_status(parser(tokens));
			free(input);
		}
	}
	hook_environ(NULL, 1);
	return (last_exit_status(-1));
}
