/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_token_to_remove_quotes.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 14:33:59 by myokogaw          #+#    #+#             */
/*   Updated: 2024/05/02 19:54:45 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_content_in_squote(char *lexeme, int pos, int fd)
{
	pos++;
	while (lexeme[pos] != '\'')
		pos += write(fd, &lexeme[pos], 1);
	pos++;
	return (pos);
}

int	get_content_in_dquote(char *lexeme, int pos, int fd)
{
	pos++;
	while (lexeme[pos] != '\"')
		pos += write(fd, &lexeme[pos], 1);
	pos++;
	return (pos);
}

void	change_token(t_dlist *token, char *path)
{
	char	*new_lexeme;
	int		fd;

	fd = ft_open_fd(path, OPEN_RD);
	new_lexeme = get_next_line(fd);
	free(token->tok->lex);
	token->tok->lex = new_lexeme;
	close (fd);
	unlink(path);
	return ;
}

void	remove_quotes(t_dlist *token)
{
	char	*lexeme;
	int		i;
	int		fd;

	fd = ft_open_fd("remove_quotes_file", OPEN_WR);
	i = 0;
	lexeme = token->tok->lex;
	while (lexeme[i])
	{
		if (lexeme[i] == '\'')
			i = get_content_in_squote(lexeme, i, fd);
		else if (lexeme[i] == '\"')
			i = get_content_in_dquote(lexeme, i, fd);
		else
			i += write(fd, &lexeme[i], 1);
	}
	close(fd);
	change_token(token, "remove_quotes_file");
}

void	send_token_to_remove_quotes(t_dlist **tokens)
{
	t_dlist	*token;

	token = *tokens;
	while (token)
	{
		remove_quotes(token);
		if (token->next == NULL)
			break ;
		token = token->next;
	}
	return ;
}
