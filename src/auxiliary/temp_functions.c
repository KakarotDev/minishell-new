/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parthur- <parthur-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:33:18 by parthur-          #+#    #+#             */
/*   Updated: 2024/05/08 17:36:17 by parthur-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	matrix_len(char **mat)
{
	int	i;

	i = 0;
	while (mat[i] != NULL)
		i++;
	return (i);
}