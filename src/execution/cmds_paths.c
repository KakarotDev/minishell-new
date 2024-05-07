/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parthur- <parthur-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 18:09:03 by parthur-          #+#    #+#             */
/*   Updated: 2024/05/07 18:11:00 by parthur-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pipex	*looking_for_the_right_ones(t_pipex *p)
{
	t_aux	aux;

	aux.j = 0;
	aux.i = 0;
	aux.k = 0;
	p->paths.right_paths = (char **)ft_calloc(p->argc - 2, sizeof(char *));
	while (aux.j < p->argc - 3)
	{
		aux.i = 0;
		while (p->paths.mat_path[aux.i] != NULL)
		{
			aux.path = ft_strjoin(p->paths.mat_path[aux.i],
					p->cmds.args[aux.k][0]);
			if (access(aux.path, X_OK) == 0)
			{
				p->paths.right_paths[aux.j] = aux.path;
				break ;
			}
			free(aux.path);
			aux.i++;
		}
		aux.j++;
		aux.k++;
	}
	return (p);
}

char	*get_first_arg(t_pipex *p, int start, int j)
{
	int		i;
	char	*arg;

	i = 0;
	arg = (char *)ft_calloc(start, sizeof(char));
	while (i < start - 1)
	{
		arg[i] = p->cmds.commands[j][i];
		i++;
	}
	return (arg);
}

char	**get_args(t_pipex *p, int j)
{
	int		start;
	int		len;
	char	**result;
	char	control;

	start = 0;
	len = 0;
	result = (char **)ft_calloc(3, sizeof(char *));
	while (p->cmds.commands[j][start] != 34
		&& p->cmds.commands[j][start] != 39)
		start++;
	control = p->cmds.commands[j][start];
	len = start + 1;
	while (p->cmds.commands[j][len] != control)
		len++;
	len = len - start;
	result[0] = get_first_arg(p, start, j);
	result[1] = ft_substr(p->cmds.commands[j], start + 1, len - 1);
	return (result);
}

t_pipex	*get_flags(t_pipex *p)
{
	int	i;
	int	j;

	i = 2;
	j = 0;
	p->cmds.args = (char ***)ft_calloc(p->argc - 2, sizeof(char **));
	while (i < p->argc - 1)
	{
		if (ft_strchr(p->cmds.commands[j], 34)
			|| ft_strchr(p->cmds.commands[j], 39))
		{
			p->cmds.args[j] = get_args(p, j);
			i++;
			j++;
		}
		else
		{
			p->cmds.args[j] = ft_split(p->argv[i], ' ');
			i++;
			j++;
		}
	}
	return (p);
}

void	get_cmds(t_pipex *p)
{
	int	i;
	int	j;

	j = 0;
	i = 2;
	p->cmds.commands = (char **)ft_calloc(p->argc - 2, sizeof(char *));
	while (i < p->argc - 1)
	{
		p->cmds.commands[j] = p->argv[i];
		j++;
		i++;
	}
	p = get_flags(p);
}

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
	p = looking_for_the_right_ones(p);
	free_mat_pipex(p->paths.mat_path);
}