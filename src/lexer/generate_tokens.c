/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 02:28:50 by myokogaw          #+#    #+#             */
/*   Updated: 2024/03/30 02:28:50 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_all_lexemes(char *file)
{
	int				fd;
	char			*line;
	char			*all_content;
	char			*temp;
	char			**all_lexemes;

	fd = ft_open_fd(file, OPEN_RD);
	line = get_next_line(fd);
	all_content = ft_strdup(NULL);
	while (line != NULL)
	{
		temp = all_content;
		all_content = ft_strjoin(all_content, line);
		free(line);
		if (temp)
			free(temp);
		line = get_next_line(fd);
	}
	all_lexemes = ft_split(all_content, '\n');
	free(all_content);
	close(fd);
	unlink(file);
	return (all_lexemes);
}

int	ft_isop(t_dlist **head, char *lexeme)
{
	int	data[3];

	ft_memset(data, 0, sizeof(data));
	data[0] = -1;
	if (!ft_strncmp(lexeme, "<<", 2))
		ft_append_dlist(head, ft_newnode_dlist(lexeme, DGREAT, data));
	else if (!ft_strncmp(lexeme, ">>", 2))
		ft_append_dlist(head, ft_newnode_dlist(lexeme, DLESS, data));
	else if (!ft_strncmp(lexeme, "|", 1))
		ft_append_dlist(head, ft_newnode_dlist(lexeme, PIPE, data));
	else if (!ft_strncmp(lexeme, ">", 1))
		ft_append_dlist(head, ft_newnode_dlist(lexeme, R_OUT, data));
	else if (!ft_strncmp(lexeme, "<", 1))
		ft_append_dlist(head, ft_newnode_dlist(lexeme, R_IN, data));
	else
		return (0);
	return (1);
}

int	validate_assignment_word(char *lex, int *var_pos, int *is_quoted)
{
	int		s_quote;
	int		d_quote;

	d_quote = 0;
	s_quote = 0;
	if (*var_pos == -1)
		*var_pos = 0;
	while (lex[*var_pos])
	{
		if ((lex[*var_pos] == '$' && d_quote == 0 && s_quote == 0)
			|| (lex[*var_pos] == '$' && d_quote == 1))
			break ;
		if (lex[*var_pos] == '\'' && s_quote == 0 && d_quote == 0)
			s_quote = 1;
		else if (lex[*var_pos] == '\'' && s_quote == 1)
			s_quote = 0;
		if (lex[*var_pos] == '\"' && d_quote == 0 && s_quote == 0)
			d_quote = 1;
		else if (lex[*var_pos] == '\"' && d_quote == 1)
			d_quote = 0;
		*var_pos += 1;
	}
	if (d_quote == 1)
		*is_quoted = 1;
	if (lex[*var_pos] == '$')
		return (1);
	return (0);
}

int	ft_isword(t_dlist **head, char *lexeme)
{
	int	data[4];

	ft_memset(data, 0, sizeof(data));
	if (ft_have_char(lexeme, '$'))
	{
		if (validate_assignment_word(lexeme, &data[0], &data[2]))
		{
			ft_append_dlist(head, ft_newnode_dlist(lexeme, 7, data));
			return (1);
		}
		ft_append_dlist(head, ft_newnode_dlist(lexeme, 6, data));
		return (1);
	}
	else
	{
		ft_append_dlist(head, ft_newnode_dlist(lexeme, 6, data));
		return (1);
	}
	return (0);
}

t_dlist	**generate_tokens(char *file)
{
	t_dlist	**dlist_tokens;
	char	**lexemes;
	int		i;
	int		j;

	dlist_tokens = (t_dlist **) ft_calloc(1, sizeof(t_dlist **));
	lexemes = get_all_lexemes(file);
	if (lexemes == NULL)
		return (NULL);
	i = 0;
	j = i;
	while (lexemes[i])
	{
		if (ft_isop(dlist_tokens, lexemes[i]))
			j++;
		else if (ft_isword(dlist_tokens, lexemes[i]))
			j++;
		if (j > i)
			i = j;
		else
			i++;
	}
	ft_free_matrix((void **) lexemes);
	return (dlist_tokens);
}
