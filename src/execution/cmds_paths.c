/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parthur- <parthur-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 18:09:03 by parthur-          #+#    #+#             */
/*   Updated: 2024/05/09 18:56:53 by parthur-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_paths(t_pipex *p)
{
	int		i;
	char	*temp;

	i = 0;
	while (ft_strncmp("PATH", p->envp[i], 4) != 0)
		i++;
	p->paths.init_path = ft_strdup(p->envp[i] + 5);
	i = 0;
	p->paths.mat_path = ft_split(p->paths.init_path, ':');
	free(p->paths.init_path);
	p->paths.mat_len = matrix_len(p->paths.mat_path);
	while (i < p->paths.mat_len)
	{
		temp = ft_strjoin(p->paths.mat_path[i], "/");
		free(p->paths.mat_path[i]);
		p->paths.mat_path[i] = temp;
		i++;
	}
}
