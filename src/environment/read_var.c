/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 23:40:06 by myokogaw          #+#    #+#             */
/*   Updated: 2024/05/06 15:25:24 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*read_var(char **environment, char *var)
{
	int		i;
	int		lenght_var;
	char	*varname;

	i = 1;
	if (!ft_isalpha(var[i]))
		return (ft_strdup(""));
	varname = ft_strjoin(var, "=");
	lenght_var = ft_strlen(varname) - 1;
	while (environment[i])
	{
		if (!ft_strncmp(environment[i], &varname[1], lenght_var))
		{
			free(varname);
			return (ft_strdup(environment[i]));
		}
		i++;
	}
	free(varname);
	return (ft_strdup(NULL));
}
