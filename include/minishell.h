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

extern volatile sig_atomic_t	g_signal;

typedef enum	e_token_type
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

typedef struct	s_token
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
} t_token_stream;

typedef enum	e_cmd_type
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

typedef struct	s_btree
{
	t_cmd_type		type;
	char			**cmd;
	struct s_btree	*left;
	struct s_btree	*right;
	char			*filename;
}	t_btree;

/* ----------- binary_tree.c ----------- */
t_btree	*create_node(t_cmd_type type, t_btree *left, t_btree *right, char **cmd);
void	free_tree(t_btree *node);

/* ----------- token_stream.c ----------- */
t_token_stream	*create_token_stream(void);
t_token			*create_token(t_token_type type, char *value);
void			add_token(t_token_stream *ts, t_token *token);
t_token_stream	*tokenize_input(char *line);
int				validate_token_sequence(t_token_stream *ts);

/* ----------- tokenizer.c ----------- */
int				process_char(t_token_stream *ts, char *line, int i);

#endif //MINISHELL_H