/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_program.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 17:01:47 by myokogaw          #+#    #+#             */
/*   Updated: 2024/05/05 19:28:14 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_program(void)
{
	t_dlist	**tokens;
	char	*input;
	char	*entrance;

	hook_environ(copy_environ(), 0);
	hook_pwd(catch_cwd(), 0);
	handle_signal();
	while (TRUE)
	{
		entrance = set_entrance();
		input = readline(entrance);
		free(entrance);
		add_history(input);
		if (input == NULL)
			return (interrupt_program(input));
		if (quoting_validation(input))
			last_exit_status(syntax_error(UNCLOSED_QUOTE, NULL, input));
		else if (*input != '\0')
		{
			tokens = lexer(input);
			parser(tokens);
			free(input);
		}
	}
	return (last_exit_status(-1));
}
