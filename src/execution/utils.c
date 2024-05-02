/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 16:48:35 by myokogaw          #+#    #+#             */
/*   Updated: 2024/05/02 17:19:18 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**tokens_to_args(t_ast *leaf, char **envp)
{
	char	**exec_matrix;
	t_dlist	*temp;
	int		i;

	exec_matrix = NULL;
	send_token_to_expansion(leaf->exec_tokens, envp);
	send_token_to_remove_quotes(leaf->exec_tokens);
	exec_matrix = (char **) ft_calloc(ft_count_tokens(leaf->exec_tokens) + 1, sizeof(char *));
	temp = *leaf->exec_tokens;
	i = 0;
	while (temp)
	{
		exec_matrix[i] = ft_strdup(temp->tok->lex);
		if (temp->next == NULL)
			break ;
		temp = temp->next;
		i++;
	}
	return (exec_matrix);
}
