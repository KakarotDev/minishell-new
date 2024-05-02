/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 11:17:40 by myokogaw          #+#    #+#             */
/*   Updated: 2024/04/26 11:17:40 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute(char **tokens, char **envp)
{
	int		pid;
	char	*path;

	if (builtins_caller(tokens) > -1)
	{
		ft_free_matrix((void **) tokens);
		return ;
	}
	path = get_path(tokens[0], envp);
	if (!path)
	{
		last_exit_status(command_not_found(path, tokens));
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		if (execve(path, tokens, envp) < 0)
		{
			ft_free_matrix((void **) tokens);
			ft_free_matrix((void **) envp);
			exit(1);
		}
	}
	ft_free_matrix((void **)tokens);
	free(path);
	last_exit_status(get_ret_process(pid));
	return ;
}

int	execution(t_ast **ast)
{
	t_ast	*leaf;
	char	**envp;

	leaf = *ast;
	envp = hook_environ(NULL, 0);
	if (leaf->type == PIPE)
		handle_pipe(leaf);
	else if (leaf->left)
		execution(&(leaf->left));
	else if (leaf->right)
		execution(&(leaf->right));
	else if (leaf->exec_tokens && *leaf->exec_tokens)
		execute(tokens_to_args(leaf, envp), envp);
	return (0);
}
