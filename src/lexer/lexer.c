/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 19:42:03 by myokogaw          #+#    #+#             */
/*   Updated: 2024/03/26 19:42:03 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handling_single_quote(char *input, int fd)
{
	if (input == NULL)
		return (input);
	input += write(fd, input, 1);
	while (*input != '\'')
		input += write(fd, input, 1);
	input += write(fd, input, 1);
	return (input);
}

char	*handling_double_quote(char *input, int fd)
{
	if (input == NULL)
		return (input);
	input += write(fd, input, 1);
	while (*input != '\"')
		input += write(fd, input, 1);
	input += write(fd, input, 1);
	return (input);
}

char	*ft_isspace(char *input, int fd)
{
	if (input == NULL)
		return (input);
	while (*input == ' ' || *input == '\t')
		input++;
	write(fd, "\n", 1);
	return (input);
}

char	*handling_ops(char *input, int fd)
{
	if (!ft_strncmp(input, "<<", 2)
		|| !ft_strncmp(input, ">>", 2))
	{
		write(fd, "\n", 1);
		input += write(fd, input, 2);
		write(fd, "\n", 1);
	}
	else if (!ft_strncmp(input, "<", 1)
		|| !ft_strncmp(input, ">", 1)
		|| !ft_strncmp(input, "|", 1))
	{
		write(fd, "\n", 1);
		input += write(fd, input, 1);
		write(fd, "\n", 1);
	}
	return (input);
}

t_dlist	**lexer(char *input)
{
	t_dlist	**tokens;
	int		fd;

	fd = ft_open_fd("_input_file1", OPEN_WR);
	while (*input != '\0' && (*input == ' ' || *input == '\t'))
		input++;
	while (*input)
	{
		if (*input == ' ')
			input = ft_isspace(input, fd);
		if (*input == '\'')
			input = handling_single_quote(input, fd);
		if (*input == '\"')
			input = handling_double_quote(input, fd);
		if (ft_have_op(input))
			input = handling_ops(input, fd);
		if (*input != '\'' && *input != '\"'
			&& *input != ' ' && *input != 0)
			input += write(fd, input, 1);
	}
	close(fd);
	tokens = generate_tokens("_input_file1");
	return (tokens);
}
