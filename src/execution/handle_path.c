/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 16:45:04 by myokogaw          #+#    #+#             */
/*   Updated: 2024/05/01 17:45:30 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**ft_append_str_matrix(char **matrix, char *str)
{
	char	*prev_str;
	int		i;

	i = 0;
	while (matrix[i])
	{
		prev_str = matrix[i];
		matrix[i] = ft_strjoin(matrix[i], str);
		free(prev_str);
		i++;
	}
	return (matrix);
}

static char	*ft_delete_start_str(char *str, char *str_to_del)
{
	int		str_to_del_len;
	int		str_len;
	char	*str_ret;

	str_to_del_len = ft_strlen(str_to_del);
	str_len = ft_strlen(str);
	str_ret = ft_substr(str, str_to_del_len, str_len);
	return (str_ret);
}

static char	**formating_paths(char **envp)
{
	int		i;
	char	*format_str;
	char	**matrix_to_ret;

	i = 0;
	while (ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	format_str = ft_delete_start_str(ft_strdup(envp[i]), "PATH=");
	matrix_to_ret = ft_split(format_str, ':');
	matrix_to_ret = ft_append_str_matrix(matrix_to_ret, "/");
	free(format_str);
	return (matrix_to_ret);
}

char	*get_path(char *command, char **envp)
{
	int		i;
	char	*path;
	char	**format_paths;
	char	*path_to_validate;

	format_paths = formating_paths(envp);
	path = NULL;
	i = 0;
	while (format_paths[i])
	{
		path_to_validate = \
		ft_strjoin(format_paths[i], command);
		if (access(path_to_validate, F_OK | X_OK) == 0 && !path)
			path = ft_strdup(path_to_validate);
		free(path_to_validate);
		i++;
	}
	ft_free_matrix((void **) format_paths);
	return (path);
}
