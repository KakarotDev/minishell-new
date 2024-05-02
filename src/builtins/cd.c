/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 15:58:57 by myokogaw          #+#    #+#             */
/*   Updated: 2024/05/01 19:47:10 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	ft_count_el(char **matrix)
{
	int	i;

	i = 0;
	if (!matrix)
		return (i);
	if (!*matrix)
		return (i);
	while (matrix[i])
		i++;
	return (i);
}

// Erros do comando cd: 1.
// variável de ambiente home não setada, e chama-se o commando cd sem argumentos, dar mensagem de erro
// bash: cd: HOME not set
// 2. Passar mais de um argumento para o comando cd, too many arguments
int	cd(char **matrix)
{
	char	*path;
	int		args;
	
	args = ft_count_el(matrix);
	if (args > 2)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return (1);
	}
	if (args == 1)
	{
		path = get_content_var(read_var(hook_environ(NULL, 0), "HOME"));
		if (!path)
		{
			ft_putstr_fd("cd: HOME not set\n", 2);
			return (1);
		}
		else
		{
			if (chdir(path) == -1)
			{
				perror("");
				return (1);
			}
			return (0);
		}
	}
	if (chdir(matrix[1]) == -1)
	{
		perror("");
		return (1);
	}
	return (0);
}
