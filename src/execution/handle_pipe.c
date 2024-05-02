/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 16:46:36 by myokogaw          #+#    #+#             */
/*   Updated: 2024/05/02 20:08:55 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_fork(t_ast *leaf, int first, int fildes[2])
{
	if (first)
		dup2(fildes[1], STDOUT_FILENO);
	else if (!first)
		dup2(fildes[0], STDIN_FILENO);
	close(fildes[0]);
	close(fildes[1]);
	if (first)
	{
		execution(&leaf->left);
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		close(STDERR_FILENO);
		return ;
	}
	else if (!first)
	{
		execution(&leaf->right);
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		close(STDERR_FILENO);
		return ;
	}
}

void	handle_pipe(t_ast *leaf)
{
	int		fildes[2];
	pid_t	forks[2];

	if (!pipe(fildes))
	{
		forks[0] = fork();
		if (forks[0] == -1)
			perror("Error\n");
		if (forks[0] == 0)
			handle_fork(leaf, 1, fildes);
		forks[1] = fork();
		if (forks[1] == -1)
			perror("Error\n");
		if (forks[1] == 0)
			handle_fork(leaf, 0, fildes);
		close(fildes[0]);
		close(fildes[1]);
		get_ret_process(forks[0]);
		last_exit_status(get_ret_process(forks[1]));
	}
	return ;
}
