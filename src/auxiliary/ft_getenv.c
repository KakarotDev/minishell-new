/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 20:13:06 by myokogaw          #+#    #+#             */
/*   Updated: 2024/05/05 20:28:20 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(char *var)
{
	char	*var_and_value;
	char	*value;

	var_and_value = read_var(hook_environ(NULL, 0), var);
	value = get_content_var(var_and_value);
	free(var_and_value);
	if (!*value)
	{
		free(value);
		return (NULL);
	}
	return (value);
}
