/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 14:19:55 by nbenhami          #+#    #+#             */
/*   Updated: 2025/03/07 14:19:55 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <signal.h>
# include <errno.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/stat.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include <sys/ioctl.h>
# include "color.h"

# define ERR_NL "minishell: syntax error near unexpected token `newline'\n"
# define ERR_REDIR "minishell: syntax error near unexpected token `redir'\n"

extern int						g_exit_code;
extern volatile sig_atomic_t	g_signal;

typedef enum e_token_type
{
	TOKEN_COMMAND,
	TOKEN_PIPE,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_SEMICOLON,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_HEREDOC,
	TOKEN_APPEND,
	TOKEN_WORD,
	TOKEN_QUOTED
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
}	t_token;

typedef struct s_token_stream
{
	t_token		**tokens;
	int			size;
	int			capacity;
	int			current;
}	t_token_stream;

typedef enum e_cmd_type
{
	NODE_COMMAND,
	NODE_PIPE,
	NODE_AND,
	NODE_OR,
	NODE_SEMICOLON,
	NODE_REDIR_IN,
	NODE_REDIR_OUT,
	NODE_HEREDOC,
	NODE_APPEND
}	t_cmd_type;

typedef struct s_btree
{
	t_cmd_type		type;
	char			**cmd;
	struct s_btree	*left;
	struct s_btree	*right;
	char			*redir_in;
	char			*redir_out;
	char			*heredoc;
	char			*append;
	int				status;
}	t_btree;

/* ----------- binary_tree.c ----------- */

t_btree			*create_node(t_cmd_type type, t_btree *left,
					t_btree *right, char **cmd);
void			free_tree(t_btree *node);

/* ----------- token_stream.c ----------- */

void			free_token_stream(t_token_stream *ts);
t_token_stream	*create_token_stream(void);
t_token			*create_token(t_token_type type, char *value);
void			add_token(t_token_stream *ts, t_token *token);
t_token_stream	*tokenize_input(char *line, char **env);
int				validate_token_sequence(t_token_stream *ts);

/* ----------- tokenizer.c ----------- */

int				process_char(t_token_stream *ts, char *line, int i, char **env);

t_btree			*parse_input(t_token_stream *tokens);
t_btree			*parse_sequence(t_token_stream *tokens);
t_btree			*parse_logical(t_token_stream *tokens);
t_btree			*parse_pipeline(t_token_stream *tokens);
t_btree			*parse_command(t_token_stream *tokens);
t_btree			*parse_redirection(t_token_stream *tokens);
void			consume_token(t_token_stream *tokens);
int				current_token_is(t_token_stream *tokens, t_token_type type);

int				execute_path(char **cmd, char **envp);


void			execute_tree(t_btree *tree, char **envp);

int				handle_quoted_string(t_token_stream *ts,
					char *line, int i, char **env);
/*--------------------------BUILT IN-----------------------------------------*/
void			ft_echo(char **args);
void			ft_cd(char *path);
void			ft_pwd(void);
void			ft_export(char *var, char **envp);
void			ft_unset(char *var, char **envp);
void			ft_env(char **envp);
void			ft_exit(char *arg);
int				built_in_check(char *str, char **args, char **envp);

/*-----------------------------UTILS------------------------------------------*/
void			get_env(char **envp);
void			free_tab(char **tab);
char			**sim_glob(char **tab, char c);
char			**ft_tab_realloc(char **tab, size_t new_size);
void			ft_print_env(int export);

/*-----------------------------UTILS_2----------------------------------------*/
void			print_sort_export(void);
void			swap_tab(char **a, char **b);
void			set_export(void);
int				ft_tablen(char **tab);
int				contain_alpha(char *str);

/*-----------------------------EXIT------------------------------------------*/
void			set_exit_code(int code);
int				get_exit_code(void);
int				sim_exit(int code, char c);


#endif //MINISHELL_H
