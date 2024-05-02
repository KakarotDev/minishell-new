/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crud_environ.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 23:40:06 by myokogaw          #+#    #+#             */
/*   Updated: 2024/05/02 17:15:50 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*read_var(char **environment, char *var)
{
	int		i;
	int		lenght_var;

	i = 1;
	if (!ft_isalpha(var[i]))
		return (ft_strdup(""));
	lenght_var = ft_strlen(var) - 1;
	while (environment[i])
	{
		if (!ft_strncmp(environment[i], var + 1, lenght_var))
			return (ft_strdup(environment[i]));
		i++;
	}
	return (ft_strdup(NULL));
}
