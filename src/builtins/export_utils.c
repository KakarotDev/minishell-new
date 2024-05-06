/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 20:07:55 by myokogaw          #+#    #+#             */
/*   Updated: 2024/05/05 20:11:03 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	report_error_export(void)
{
	ft_putstr_fd("Error\n export: not a valid identifier\n", 2);
	return (1);
}

void	ft_printf_variables_export(char *variable)
{
	write(1, "declare -x ", 11);
	while (*variable != '=' && *variable)
		variable += write(1, variable, 1);
	if (!*variable)
	{
		write(1, "\n", 1);
		return ;
	}
	else
	{
		variable += write(1, variable, 1);
		write(1, "\"", 1);
	}
	while (*variable)
		variable += write(1, variable, 1);
	write(1, "\"\n", 2);
	return ;
}

int	show_variables(char **envp)
{
	char	upper;
	char	lower;
	int		i;

	upper = 'A';
	lower = 'a';
	while (lower < 'z' && upper < 'Z')
	{
		i = 0;
		while (envp[i])
		{
			if (envp[i][0] == lower || envp[i][0] == upper || envp[i][0] == '_')
				ft_printf_variables_export(envp[i]);
			i++;
		}
		lower++;
		upper++;
	}
	return (EXIT_SUCCESS);
}
