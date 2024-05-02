/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interrupt_program.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 22:53:36 by myokogaw          #+#    #+#             */
/*   Updated: 2024/04/29 22:53:36 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	interrupt_program(char *input)
{
	hook_environ(NULL, 1);
	free(input);
	rl_clear_history();
	printf("\n");
	return (0);
}
