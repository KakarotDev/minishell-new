/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 16:42:43 by myokogaw          #+#    #+#             */
/*   Updated: 2024/02/23 16:42:43 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# ifdef __cplusplusbash
	extern "C" {
# endif

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <errno.h>
# include <fcntl.h>
# include <wait.h>
# include "libft.h"

// Boolean defines
# define TRUE 1
# define FALSE 0

// Open defines
# define OPEN_WR 1
# define OPEN_RD 2

// AST defines
# define RIGHT 3
# define LEFT 4

// Syntax error defines
# define UNCLOSED_QUOTE 5
# define UNEXPECTED 6

// Define errors for cd command;
#define TOOMANY 3
#define NOTSETHOME 2
#define ERRNO 1

enum	e_type
{
	DGREAT = 1,
	DLESS,
	PIPE,
	R_OUT,
	R_IN,
	WORD,
	ASSIGNMENT_WORD,
	CMD
};

typedef struct s_token {
	enum e_type		type;
	char			*lex;
	int				data[4];
}	t_token;

typedef struct s_dlist {
	t_token			*tok;
	struct s_dlist	*next;
	struct s_dlist	*prev;
}	t_dlist;

typedef struct s_ast
{
	enum e_type			id_t;
	struct s_no_arvore	*esq;
	struct s_no_arvore	*dir;
	char		*path;
	char		**cmd;
	int			index;
}	t_ast;

typedef struct s_cmds
{
	char	**commands;
	char	***args;
}	t_cmds;

typedef struct s_paths
{
	char	**right_paths;
	char	*init_path;
	char	**mat_path;
	int		mat_len;
}	t_paths;

typedef struct s_aux
{
	int		i;
	int		j;
	int		k;
	char	*path;
}	t_aux;

typedef struct s_fd_files
{
	int	in;
	int	out;
}	t_fd_files;

typedef struct s_pipex
{
	t_cmds		cmds;
	t_paths		paths;
	t_fd_files	fd_files;
	enum e_type	id_t;
	char		**argv;
	int			argc;
	char		**envp;
	int			pipe_fd[2];
	int			fork_id;
	int			c;
	int			status;
	int			fd_exec[2];
	int			exit_fd;
	int			input_fd;
	int			f_id;
}	t_pipex;

// Print functions
void	ft_print_matrix(char **matrix);
void	ft_print_dlist(t_dlist **head);
void	ft_print_ast(t_ast **root);

// Auxiliary functions
char	**hook_environ(char **envp, int free);
char	*ft_strndup(char const *s, unsigned int start, size_t len);
char	*ft_isspace(char *input, int fd);
char	*get_content_var(char *var);
void	free_struct_token(t_token *tok);
void	ft_free_ast(t_ast **root);
void	ft_free_matrix(void **matrix);
void	ft_destructor_struct(t_dlist **struct_to_clean);
void	ft_cpy_array_data(int *dst, int *src, int size);
void	close_fds(int fd_max);
int		ft_open_fd(char *path, int flags);
int		ft_have_char(char *str, char c);
int		ft_have_op(char *input);
int		ft_open_fork(void);
int		ft_is_redirect(enum e_type type);
int		get_ret_process(int pid);
int		last_exit_status(int exit_status);
int		command_not_found(char *path, char **matrix);
int		ft_count_tokens(t_dlist **exec_tokens);
int		run_program(void);
int		have_pipe(t_dlist *tokens);
char	*catch_cwd(void);
char	*hook_pwd(char *n_pwd, int to_free);
char	*set_entrance(void);
char	*ft_getenv(char *var);

// dlist procedures
int		ft_dlist_have_type(t_dlist **tokens, enum e_type type);
void	ft_dlist_delete_from(t_dlist *start_node);
void	ft_append_dlist(t_dlist **head, t_dlist *node);
t_dlist	*ft_dlst_last(t_dlist *node);
t_dlist	*ft_newnode_dlist(char *lexeme, enum e_type type,
		int expansion_data[3]);
t_dlist	*ft_add_currnext(t_dlist *token, t_dlist *new_token, int iteration);
t_dlist	*ft_cpy_node(t_dlist *node);
t_dlist	*ft_dlist_last_occur(t_dlist **tokens, enum e_type type);
t_dlist	**ft_cpy_dlst(t_dlist *start_point);

// Environment
char	**copy_environ(void);

// Environment procedures
char	*read_var(char **environment, char *var);

// Lexer
t_dlist	**lexer(char *input);
t_dlist	**generate_tokens(char *file);
char	**get_all_lexemes(char *file);
int		validate_assignment_word(char *lex, int *var_pos, int *is_quoted);
int		quoting_validation(char *input);

// Signal
void	handle_signal(void);

// Expansions
void	send_token_to_expansion(t_dlist **tokens, char **environment);
void	var_expansion(t_dlist *token, char **environment);

// Remove quotes
void	send_token_to_remove_quotes(t_dlist **tokens);
void	remove_quotes(t_dlist *token);

// Handle redirections
int		check_redirections(t_dlist **tokens);

// Handle pipes
int		check_pipes(t_dlist **tokens);

// Handle error
int		syntax_error(int type, t_dlist **tokens, char *input);

// Parser
void	parser(t_dlist **tokens);
int		parser_validation(t_dlist **tokens);

// AST procedures

// Builtins
int		builtins_caller(char **matrix);
int		cd(char **matrix);
int		export(char **matrix);
int		echo(char **matrix);
int		pwd(void);
int		env(char **args);
int		report_error_export(void);
int		show_variables(char **envp);
void	ft_printf_variables_export(char *variable);

// Interrupt program
int		interrupt_program(char *input);

// Exec

#  ifdef __cplusplus
	} // extern "C"
#  endif

# endif
