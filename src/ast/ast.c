/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parthur- <parthur-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 18:00:50 by parthur-          #+#    #+#             */
/*   Updated: 2024/05/09 21:58:52 by parthur-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_dlist	*free_chunk_list(t_dlist *tokens)
{
	while (tokens->next != NULL)
		tokens = tokens->next;
	while (tokens->tok->type != PIPE)
	{
		tokens = tokens->prev;
		free(tokens->next);
	}
	tokens = tokens->prev;
	free(tokens->next);
	tokens->next = NULL;
	return (tokens);
}

char	*cria_path(t_dlist *tokens, t_pipex *p)
{
	t_dlist	*aux_t;
	int		i;
	char	*aux_path;
	aux_t = tokens;

	i = 0;
	while (aux_t->next != NULL)
		aux_t = aux_t->next;
	while (aux_t->tok->type != PIPE && aux_t->prev != NULL)
		aux_t = aux_t->prev;
	while (aux_t->tok->type != WORD)
		aux_t = aux_t->next;
	while (p->paths.mat_path[i] != NULL)
	{
		aux_path = ft_strjoin(p->paths.mat_path[i], aux_t->tok->lex);
		if (access(aux_path, X_OK) == 0)
			return (aux_path);
		free(aux_path);
		i++;
	}
	return (NULL);
}

char	**cria_mat_cmds(t_dlist *tokens) //diminuir linhas
{
	t_dlist	*aux;
	char	**mat_exc;
	size_t	mat_exec_len;
	int		i;

	mat_exec_len = 1;
	aux = tokens;
	i = 0;
	while (aux->next != NULL)
		aux = aux->next;
	while (aux->tok->type != PIPE && aux->prev != NULL)
	{
		if (aux->tok->type == WORD)
			mat_exec_len++;
		aux = aux->prev;
	}
	mat_exc = (char **)calloc(sizeof(char *), mat_exec_len); //trocar pela ft_calloc ATENÇÂO ATENÇÂO !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	while (aux != NULL)
	{
		if (aux->tok->type == WORD)
		{
			mat_exc[i] = aux->tok->lex;
			i++;
		}	
		aux = aux->next;
	}
	return (mat_exc);
}

t_ast	*cria_no_cmd(t_dlist *tokens, t_pipex *p)
{
	t_ast	*no_cmd;

	no_cmd = (t_ast *)malloc(sizeof(t_ast));
	no_cmd->type = WORD;
	no_cmd->esq = NULL;
	no_cmd->dir = NULL;
	no_cmd->path = cria_path(tokens, p);
	no_cmd->cmd = cria_mat_cmds(tokens);
	no_cmd->index = 0;
	return (no_cmd);
}

t_ast	*cria_no_arv(t_dlist *tokens, t_pipex *p)
{
	t_ast	*no_pipe;

	no_pipe = (t_ast *)malloc(sizeof(t_ast));
	no_pipe->type = PIPE;
	no_pipe->esq = NULL;
	no_pipe->dir = cria_no_cmd(tokens, p);
	no_pipe->path = NULL;
	no_pipe->cmd = NULL;
	no_pipe->index = 0;
	return (no_pipe);
}

t_ast	*adiciona_no(t_ast *raiz, t_ast *no)
{
	if (raiz == NULL)
		return (no);
	raiz->esq = adiciona_no(raiz->esq, no);
	return (raiz);
}

t_ast	*cria_arvore(t_dlist **t, t_pipex *p)
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
			esq = cria_no_arv(aux, p);
			aux = free_chunk_list(t[0]);
			//printf("%s\n", aux->tok->lex);
			//printf("TYPE NO ESQ %d, TYPE NO DIR %d, PATH NO DIR = %s, FIRST CMD NO DIR = %s\n", esq->type, esq->dir->type, esq->dir->path, esq->dir->cmd[0]);
			raiz = adiciona_no(raiz, esq);
		}
		else
		{
	 		esq = cria_no_cmd(aux, p);
			raiz = adiciona_no(raiz, esq);
		}
		i--;
	}
	return (raiz);
}

// void	exec_cmd(t_ast *raiz, t_pipex *p)
// {
// 	int	f_id;

// 	f_id = fork();
// 	if (f_id == 0)
// 	{	
// 		if (raiz->index != 3)
// 			dup2(p->fd_exec[1], 1);
// 		if (raiz->index != 1)
// 			dup2(p->fd_exec[0], 0);
// 		close_fds(p->pipe_fd[1]);
// 		execve(raiz->path, raiz->cmd, p->envp);
// 	}
// 	if (raiz->index != 1)
// 		close(p->fd_exec[0]);
// 	if (raiz->index != 3)
// 		close(p->fd_exec[1]);
// }

// void	first_command_organizer(t_ast *raiz, t_pipex *p)
// {
// 	p->fd_exec[1] = p->pipe_fd[1];
// 	p->fd_exec[0] = 0;
// 	exec_cmd(raiz->esq, p);
// 	close_fds(p->pipe_fd[1]);
// 	exit(0);
// }

// void	standard_command_organizer(t_ast *raiz, t_pipex *p)
// {
// 	if (raiz->dir->index != 3)
// 		p->fd_exec[1] = p->exit_fd;
// 	p->fd_exec[0] = p->input_fd;
// 	exec_cmd(raiz->dir, p);
// 	if (raiz->dir->index == 3)
// 		close(p->pipe_fd[1]);
// }

// void	tree_exec(t_ast *raiz, t_pipex *p, int fd)
// {
// 	p->exit_fd = fd;
// 	if (pipe(p->pipe_fd) == -1)
// 		return ;
// 	p->input_fd = p->pipe_fd[0];
// 	if (raiz->esq->id_t == PIPE)
// 	{
// 		p->f_id = fork();
// 		if (p->f_id == 0)
// 		{
// 			fd = p->pipe_fd[1];
// 			tree_exec(raiz->esq, p, fd);
// 			close_fds(p->pipe_fd[1]);
// 			exit(0);
// 		}
// 		wait(NULL);
// 	}
// 	else
// 	{
// 		p->f_id = fork();
// 		if (p->f_id == 0)
// 			first_command_organizer(raiz, p);
// 		waitpid(p->f_id, NULL, 0);
// 	}
// 	standard_command_organizer(raiz, p);
// }

void	ast_function(t_pipex *p, t_dlist **tokens)
{
	t_ast	*raiz;
	int		i;

	i = 0;
	tokens[0]->pipes = have_pipe(tokens[0]);
	get_paths(p);
	raiz = cria_arvore(tokens, p);
	// printf("TYPE NO ESQ %d, TYPE NO DIR %d, PATH NO DIR = %s, FIRST CMD NO DIR = %s\n", raiz->type, raiz->dir->type, raiz->dir->path, raiz->dir->cmd[0]);
	// printf("TYPE NO ESQ %d, TYPE NO DIR %d, PATH NO DIR = %s, FIRST CMD NO DIR = %s\n", raiz->esq->type, raiz->esq->dir->type, raiz->esq->dir->path, raiz->esq->dir->cmd[0]);
	// printf("TYPE NO ESQ %d, TYPE NO DIR %d, PATH NO DIR = %s, FIRST CMD NO DIR = %s\n", raiz->type, raiz->esq->esq->type, raiz->esq->esq->path, raiz->esq->esq->cmd[0]);
	// tree_exec(raiz, p, STDOUT_FILENO);
}
