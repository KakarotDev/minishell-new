/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_caller.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:00:17 by myokogaw          #+#    #+#             */
/*   Updated: 2024/05/01 19:51:37 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtins_caller(char **matrix)
{
	int	exit_status;

	exit_status = -1;
	if (!ft_strncmp(matrix[0], "echo", ft_strlen(matrix[0])))
		exit_status = echo(matrix);
	else if (!ft_strncmp(matrix[0], "export", ft_strlen(matrix[0])))
		exit_status = export(matrix);
	else if (!ft_strncmp(matrix[0], "cd", ft_strlen(matrix[0])))
		exit_status = cd(matrix);
	if (exit_status != -1)
		return(last_exit_status(exit_status));
	return (exit_status);
}
