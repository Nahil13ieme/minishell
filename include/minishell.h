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
/******************************INCLUDE****************************************/

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
/*******************************DEFINE****************************************/

# define ERR_NL "minishell: syntax error near unexpected token `newline'\n"
# define ERR_REDIR "minishell: syntax error near unexpected token `redir'\n"

extern volatile sig_atomic_t	g_signal;

/*******************************STRUCT****************************************/

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
	int				status;
	int				child;
	t_cmd_type		type;
	char			**cmd;
	struct s_btree	*left;
	struct s_btree	*right;
	char			*file;
}	t_btree;

/******************************FILES**************************************** */

/* ----------------------------BINARY_TREE-----------------------------------*/
t_btree			*create_node(t_cmd_type type, t_btree *left,
					t_btree *right, char **cmd);
void			free_tree(t_btree *root);

/*-----------------------------BUILT IN--------------------------------------*/
void			ft_echo(char **args);
int				ft_cd(char *path);
void			ft_pwd(void);
void			ft_export(char *var, char **envi);
void			ft_unset(char *var);

/* ------------------------EXECUTE_HEREDOC---------------------------------- */
void			execute_heredoc(t_btree *tree, char **envp);

/* ----------------------EXECUTE_REDIRECTION-------------------------------- */
void			exit_error(char *msg);
//static void		execute_redir_in(t_btree *tree, char **envp);
//static void		execute_redir_out(t_btree *tree, char **envp);
//static void		execute_append(t_btree *tree, char **envp);
void			execute_redirection(t_btree *tree, char **envp);

/*---------------------------EXECUTE_TREE------------------------------------*/
//static void		execute_and(t_btree *tree, char **envp);
//static void		execute_or(t_btree *tree, char **envp);
//static pid_t	execute_pid(t_btree *tree, char **envp, int *fd, int fileno);
//static void		execute_pipeline(t_btree *tree, char **envp);
void			execute_tree(t_btree *tree, char **envp);

/*-------------------------------EXIT----------------------------------------*/
void			set_exit_code(int code);
int				get_exit_code(void);
int				sim_exit(int code, char c);
void			ft_exit(char *arg);

/*-----------------------------GET_PROMPT------------------------------------*/
char			*get_username(void);
char			*make_prompt(void);

/*--------------------------PARSE_INPUT_UTILS--------------------------------*/
//static char		**create_args(t_token_stream *tokens);
t_btree			*parse_command(t_token_stream *tokens);
void			consume_token(t_token_stream *tokens);
int				current_token_is(t_token_stream *tokens, t_token_type type);

/*----------------------------PARSE_INPUT------------------------------------*/
t_btree			*parse_input(t_token_stream *ts);
t_btree			*parse_sequence(t_token_stream *ts);
t_btree			*parse_logical(t_token_stream *ts);
t_btree			*parse_pipeline(t_token_stream *ts);
t_btree			*parse_redirection(t_token_stream *ts);

/*---------------------------PATH_EXECUTE------------------------------------*/
//static void		free_paths(char **paths);
char			*find_path(char *cmd, char **envp);
//static int		execute_child(char *path, char **cmd, char **envp);
int				execute_path(char **cmd, char **envp, int child);
int				built_in_check(char *str, char **args, char **envp);

/*-----------------------------PROCESS---------------------------------------*/
void			process_line(char *line, char **envp);

/*--------------------------SIGNAL_HANDLER-----------------------------------*/
void			setup_signals(void);
void			handle_sigint(int sig);
void			setup_child_signals(void);

/*---------------------------TOKEN_STREAM------------------------------------*/
void			add_token(t_token_stream *stream, t_token *token);
t_token			*create_token(t_token_type type, char *value);
t_token_stream	*create_token_stream(void);
void			free_token_stream(t_token_stream *ts);
t_token_stream	*tokenize_input(char *line, char **env);

/*-------------------------TOKENIZER_QUOTES----------------------------------*/
//static char		*handle_double_quote(char *line, int *i, char **env);
char			*handle_quoted_string(char *line, int *i, char **env);
//static char		*handle_word(char *line, int *i);
int				handle_segment(t_token_stream *ts, char *line,
					int i, char **env);

/*----------------------------TOKENIZER--------------------------------------*/
//static int		handle_double_tokens(t_token_stream *ts, char *line, int i);
//static int		handle_single_tokens(t_token_stream *ts, char *line, int i);
char			*handle_env_variable(char *line, int *i, char **env);
int				process_char(t_token_stream *ts, char *line, int i,
					char **env);

/*---------------------------TOKENS_UTILS------------------------------------*/
//static int		is_control(t_token_type type);
//static int		is_redir(t_token_type type);
//static int		validate_token_list(t_token_stream *ts);
int				validate_token_sequence(t_token_stream *ts);

/*-----------------------------UTILS_2---------------------------------------*/
void			swap_tab(char **a, char **b);
void			print_sort_export(void);
void			set_export(void);
//void			modifi_env_export(char *var);
void			set_path(void);

/*-------------------------UTILS_BUILT_IN------------------------------------*/
int				ft_while_echo(char **args, int i, int j);
int				ft_if_export(char **envi, int i, char *var, char *equal_pos);
void			ft_if_unset(char **export, char *var, int len, int i);

/*----------------------------UTILS_ENV--------------------------------------*/
void			get_env(char **envp);
void			free_glob(void);
void			ft_env(char **envp);
char			*return_env(char *str);

/*--------------------------UTILS_EXECUTE------------------------------------*/
void			ft_if_execute_andor(t_btree *tree, char **envp);

/*---------------------------UTILS_EXPORT------------------------------------*/
char			**sim_glob(char **tab, char c);
char			**ft_tab_realloc(char **tab, size_t new_size);
void			add_export(char **tab, char *str);
void			ft_while_print_export(char **tab, int i, int j);
int				ft_while_set_export(void);
void			ft_if_modify_export(char *equal_pos, char *var, char **envi,
					char **export);

/*---------------------------UTILS_HANDLE------------------------------------*/
//static char		*handle_simple_quote(char *line, int *i);
//static void		double_quote_segment(char **segment, char *line, int *i);
int				ft_while_handle_segment(char *line, char **env, char *word,
					int i, char **segment);

/*----------------------------UTILS_TREE-------------------------------------*/
void			print_tree(t_btree tree);
t_btree			*set_root(t_btree *root, char c);

/*-------------------------------UTILS---------------------------------------*/
void			get_env(char **envp);
void			free_tab(char **tab);
void			free_glob(void);
char			**sim_glob(char **tab, char c);
char			**ft_tab_realloc(char **tab, size_t new_size);
void			ft_print_env(int export);
int				ft_tablen(char **tab);

#endif //MINISHELL_H
