/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parthur- <parthur-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 18:00:50 by parthur-          #+#    #+#             */
/*   Updated: 2024/05/08 18:13:23 by parthur-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*cria_no_arv(t_dlist *token)
{
	t_ast	*no;
	no = (t_ast *)malloc(sizeof(t_ast));
	no->id_t = token->id_t;
	no->esq = NULL;
	no->dir = NULL;
	no->path = NULL;
	no->cmd = NULL;
	no->index = 0;
	if (token->path)
		no->path = token->path;
	if (token->cmd)
		no->cmd = token->cmd;
	if (token->index != 0)
		no->index = token->index;
	return (no);
}

t_ast	*adiciona_no(t_ast *raiz, t_ast *no)
{
	if (raiz == NULL)
		return (no);
	raiz->esq = adiciona_no(raiz->esq, no);
	return (raiz);
}

t_ast	*cria_arvore(t_dlist **t)
{
	t_ast	*raiz;
	t_ast	*esq;
	t_dlist		*aux;
	int			i;
	
	i = t[0]->pipes;
	aux = t[0];
	raiz = NULL;
	while (i >= 0)
	{
		if (i > 0)
		{
			esq = cria_no_arv(aux->prev);
			esq->dir = cria_no_arv(aux);
			raiz = adiciona_no(raiz, esq);
			aux = aux->prev->prev;
		}
		else
		{
			esq = cria_no_arv(aux);
			raiz = adiciona_no(raiz, esq);
		}
		i--;
	}
	return (raiz);
}

void	exec_cmd(t_ast *raiz, t_pipex *p)
{
	int	f_id;

	f_id = fork();
	if (f_id == 0)
	{	
		if (raiz->index != 3)
			dup2(p->fd_exec[1], 1);
		if (raiz->index != 1)
			dup2(p->fd_exec[0], 0);
		close_fds(p->pipe_fd[1]);
		execve(raiz->path, raiz->cmd, p->envp);
	}
	if (raiz->index != 1)
		close(p->fd_exec[0]);
	if (raiz->index != 3)
		close(p->fd_exec[1]);
}

void	first_command_organizer(t_ast *raiz, t_pipex *p)
{
	p->fd_exec[1] = p->pipe_fd[1];
	p->fd_exec[0] = 0;
	exec_cmd(raiz->esq, p);
	close_fds(p->pipe_fd[1]);
	exit(0);
}

void	standard_command_organizer(t_ast *raiz, t_pipex *p)
{
	if (raiz->dir->index != 3)
		p->fd_exec[1] = p->exit_fd;
	p->fd_exec[0] = p->input_fd;
	exec_cmd(raiz->dir, p);
	if (raiz->dir->index == 3)
		close(p->pipe_fd[1]);
}

void	tree_exec(t_ast *raiz, t_pipex *p, int fd)
{
	p->exit_fd = fd;
	if (pipe(p->pipe_fd) == -1)
		return ;
	p->input_fd = p->pipe_fd[0];
	if (raiz->esq->id_t == PIPE)
	{
		p->f_id = fork();
		if (p->f_id == 0)
		{
			fd = p->pipe_fd[1];
			tree_exec(raiz->esq, p, fd);
			close_fds(p->pipe_fd[1]);
			exit(0);
		}
		wait(NULL);
	}
	else
	{
		p->f_id = fork();
		if (p->f_id == 0)
			first_command_organizer(raiz, p);
		waitpid(p->f_id, NULL, 0);
	}
	standard_command_organizer(raiz, p);
}

void	ast_function(t_pipex *p, t_dlist **tokens)
{
	t_ast	*raiz;

	tokens[0]->pipes = have_pipe(tokens[0]);
	raiz = cria_arvore(tokens);
	tree_exec(raiz, p, STDOUT_FILENO);
}