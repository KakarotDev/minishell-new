/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_procedures.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 17:20:08 by myokogaw          #+#    #+#             */
/*   Updated: 2024/05/02 17:20:08 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_var(t_token *tok, int s_quote, int d_quote)
{
	while (tok->lex[tok->data[0]])
	{
		if (tok->lex[tok->data[0]] == '$' && s_quote == 0)
			break ;
		if (tok->lex[tok->data[0]] == '\'' && s_quote == 0 && d_quote == 0)
			s_quote = 1;
		else if (tok->lex[tok->data[0]] == '\'' && s_quote == 1)
			s_quote = 0;
		if (tok->lex[tok->data[0]] == '\"' && d_quote == 0 && s_quote == 0)
			d_quote = 1;
		else if (tok->lex[tok->data[0]] == '\"' && d_quote == 1)
			d_quote = 0;
		tok->data[0] += 1;
	}
	tok->data[1] = tok->data[0];
	if (tok->lex[++(tok->data[0])] == '?')
		return (ft_strdup("$?"));
	if (tok->lex[(tok->data[0])] == '$')
		return (ft_strdup("$$"));
	if (ft_isdigit((tok->lex[(tok->data[0])])))
		return (ft_strndup(tok->lex, tok->data[1], tok->data[0] - tok->data[1]));
	while (ft_isalnum(tok->lex[tok->data[0]]) || tok->lex[tok->data[0]] == '_')
		tok->data[0] += 1;
	return (ft_strndup(tok->lex, tok->data[1], tok->data[0] - tok->data[1]));
}

char	*get_content_var(char *var)
{
	int	i;

	i = 0;
	if (!var)
		return (ft_strdup(""));
	while (var[i] && var[i] != '=')
		i++;
	if (i == 0)
		return (ft_strdup(""));
	i++;
	return (ft_strndup(var, i, ft_strlen(var) - i));
}

static void	merging_new_token(t_dlist *token)
{
	t_dlist	*new_token;
	int		data[3];
	char	**lexemes;
	int		i;

	i = 0;
	lexemes = get_all_lexemes("/tmp/.merge_token");
	new_token = token;
	ft_memset(data, 0, sizeof(data));
	data[0] = -1;
	while (lexemes[i])
	{
		if (lexemes[i + 1] == NULL)
		{
			if (!validate_assignment_word(lexemes[i], &data[0], &data[2]))
				new_token = ft_add_currnext(new_token,
						ft_newnode_dlist(lexemes[i], 6, data), i);
			else
				new_token = ft_add_currnext(new_token,
						ft_newnode_dlist(lexemes[i], 7, data), i);
			ft_free_matrix((void **) lexemes);
			return ;
		}
		new_token = ft_add_currnext(new_token,
				ft_newnode_dlist(lexemes[i], 6, data), i);
		i++;
	}
	if (lexemes[i] == NULL)
		new_token = ft_add_currnext(new_token, ft_newnode_dlist(NULL, 6, data), i);
	ft_free_matrix((void **) lexemes);
	return ;
}

static void	writing_new_token_unquoted(t_dlist *token, char *value_var, char *var)
{
	char	*lexeme;
	int		fd;

	fd = ft_open_fd("/tmp/.merge_token", OPEN_WR);
	lexeme = token->tok->lex;
	while (token->tok->data[1]--)
		lexeme += write(fd, lexeme, 1);
	if (*value_var == ' ')
	{
		while (*value_var == ' ' && *value_var)
			value_var++;
		write(fd, "\n", 1);
	}
	while (*value_var)
	{
		if (*value_var == ' ')
		{
			while (*value_var == ' ' && *value_var)
				value_var++;
			write(fd, "\n", 1);
		}
		value_var += write(fd, value_var, 1);
	}
	while (*var == *lexeme && *var)
	{
		var++;
		lexeme++;
	}
	while (*lexeme)
		lexeme += write(fd, lexeme, 1);
	close(fd);
	merging_new_token(token);
	return ;
}

static void	writing_new_token_quoted(t_dlist *token, char *value_var, char *var)
{
	char	*lexeme;
	int		fd;

	fd = ft_open_fd("/tmp/.merge_token", OPEN_WR);
	lexeme = token->tok->lex;
	while (token->tok->data[1]--)
		lexeme += write(fd, lexeme, 1);
	while (*value_var)
		value_var += write(fd, value_var, 1);
	while (*var == *lexeme && *var)
	{
		var++;
		lexeme++;
	}
	while (*lexeme)
		lexeme += write(fd, lexeme, 1);
	close(fd);
	merging_new_token(token);
	return ;
}


//Na expansão os tokens são separados por espaço, corrigir isto. por exemplo: a="hello world" -> o resultado desta expansão será o token `hello` e o token `world`; Ok
//Cifrão que nao foi expandido e é o caracter anterior não é um delimitador, printar ele;
// Setar o ponto da ultima expansão realizada e nao sempre voltar para o começo e continuar a expandir; Ok
void	var_expansion(t_dlist *token, char **environment)
{
	char	*var;
	char	*var_content;
	char	*value_var;

	var = get_var(token->tok, 0, 0);
	var_content = read_var(environment, var);
	value_var = get_content_var(var_content);
	if (token->tok->data[2])
		writing_new_token_quoted(token, value_var, var);
	else
		writing_new_token_unquoted(token, value_var, var);
	free(var);
	free(var_content);
	free(value_var);
	return ;
}
