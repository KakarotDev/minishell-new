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

# define TRUE 1
# define FALSE 0
# define OPEN_WR 1
# define OPEN_RD 2
# define RIGHT 3
# define LEFT 4
# define UNCLOSED_QUOTE 5
# define UNEXPECTED 6

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
	int				data[3];
}	t_token;

typedef struct s_dlist {
	t_token			*tok;
	struct s_dlist	*next;
	struct s_dlist	*prev;
}	t_dlist;

typedef struct s_ast {
	t_dlist			**exec_tokens;
	int				size;
	enum e_type		type;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

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

// dlist procedures
int		ft_dlist_have_type(t_dlist **tokens, enum e_type type);
void	ft_dlist_delete_from(t_dlist *start_node);
void	ft_append_dlist(t_dlist **head, t_dlist *node);
t_dlist	*ft_dlst_last(t_dlist *node);
t_dlist	*ft_newnode_dlist(char *lexeme, enum e_type type, int expansion_data[3]);
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
int		parser(t_dlist **tokens);
int		parser_validation(t_dlist **tokens);

// AST procedures
t_ast	*ft_ast_new_leaf(t_dlist **exec_tokens, enum e_type type);
t_ast	*ft_get_last_leaf(t_ast *root, int direction);
t_ast	**ft_create_ast(t_dlist **tokens);
void	ft_ast_append_leaf(t_ast **root, t_ast *new_leaf, int side);
void	ft_constructor_ast(t_ast **root, t_dlist *last_occur);

// Builtins
int		builtins_caller(char **matrix);
int		cd(char **matrix);
int		export(char **matrix);
int		echo(char **matrix);

// Interrupt program
int		interrupt_program(char *input);

// Exec
char	**tokens_to_args(t_ast *leaf, char **envp);
char	*get_path(char *command, char **envp);
void	handle_pipe(t_ast *leaf);
int		execution(t_ast **ast);

#  ifdef __cplusplus
	} // extern "C"
#  endif

# endif