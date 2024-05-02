/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 15:59:36 by myokogaw          #+#    #+#             */
/*   Updated: 2024/05/01 19:48:33 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			if (envp[i][0] == lower || envp[i][0] == upper)
				ft_printf_variables_export(envp[i]);
			i++;
		}
		lower++;
		upper++;
	}
	return (EXIT_SUCCESS);
}

int	report_error_export(void)
{
	ft_putstr_fd("Error\n export: not a valid identifier\n", 2);
	return (1);
}

int	verify_prev_char_equal(char *assignment)
{
	char	*equal_op;

	equal_op = ft_strchr(assignment, '=');
	if (!equal_op)
		return (EXIT_SUCCESS);
	if (equal_op == assignment || (!ft_isalpha(*(--equal_op))
			&& *equal_op == '\t' && *equal_op == ' '))
		return (report_error_export());
	return (EXIT_SUCCESS);
}

int	verify_is_valid_varname(char *assignment)
{
	if (ft_isdigit(assignment[0]))
		return (report_error_export());
	while (*assignment && *assignment != '=')
	{
		if (!ft_isalnum(*assignment) && !(*assignment == '_'))
			return (report_error_export());
		assignment++;
	}
	return (EXIT_SUCCESS);
}

int	count_el_matrix_and_verify_it_have(char **matrix, char *assignment)
{
	char	*varname_end;
	int		size;
	int		i;

	i = 0;
	varname_end = ft_strchr(assignment, '=');
	if (!varname_end)
		size = ft_strlen(assignment);
	else
		size = varname_end - assignment;
	while (matrix[i])
	{
		if (!ft_strncmp(matrix[i], assignment, size))
		{
			free(matrix[i]);
			matrix[i] = ft_strdup(assignment);
			return (-1);
		}
		i++;
	}
	return (i);
}

char	**append_new_var(char **envp, char *assignment)
{
	char	**new_env;
	int		i;

	i = count_el_matrix_and_verify_it_have(envp, assignment);
	if (i == -1)
		return (envp);
	new_env = (char **) ft_calloc(i + 2, sizeof(char *));
	i = 0;
	while (envp[i])
	{
		new_env[i] = ft_strdup(envp[i]);
		i++;
	}
	new_env[i++] = ft_strdup(assignment);
	ft_free_matrix((void **) envp);
	return (new_env);
}

int	free_and_exit_export(char **envp)
{
	ft_free_matrix((void **) envp);
	return (EXIT_FAILURE);
}

int	export(char **matrix)
{
	char **envp;

	envp = hook_environ(NULL, 0);
	if (!(*(++matrix)))
		return (show_variables(envp));
	while (*matrix)
	{
		if (verify_prev_char_equal(*matrix))
			return (EXIT_FAILURE);
		if (verify_is_valid_varname(*matrix))
			return (EXIT_FAILURE);
		envp = append_new_var(envp, *matrix);
		matrix++;
	}
	return (EXIT_SUCCESS);
}
