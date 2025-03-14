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

typedef struct	t_cmd
{
	char	**cmd;
	int		argc;
	int		avac;
}	t_cmd;

typedef struct	t_exec
{
	int		avac_sc;
	int		scc;
	int		bg;
	char	*out;
	char	*in;
	char	*err;
	t_cmd	**scmds;
}	t_exec;

/* ----------- Parser.c ----------- */
void	parse_line(char *line, char ***env);
void	ft_free_split(char **split);

/* ----------- parser_utils.c ----------- */
char	*extract_segment(char *line, int *i, char *current_token, char **tokens);
char	*handle_double_quote(char *line, int *i, char **env);
char	*extract_quote(char *line, int *i, char quote);
char	*expand_variable(char *line, int *i, char **env);
//static char	*double_quote_segment(char *temp, char **env);

/* ----------- main.c ----------- */
//int	main(int ac, char **av, char **env);

/* ----------- exec_command.c ----------- */
void	exec_command(char **command, char **env);

/* ----------- builtins.c ----------- */
int		check_builtins(char *command);
void	exec_builtins(char **command, char ***env);

/* ----------- echo.c ----------- */
void	exec_echo(char **command);

/* ----------- cd.c ----------- */
void	exec_cd(char **command);

/* ----------- pwd.c ----------- */
void	exec_pwd(void);

/* ----------- export.c ----------- */
void	exec_export(char ***env, char **command);

/* ----------- unset.c ----------- */
void	exec_unset(char **command, char ***env);

/* ----------- env.c ----------- */
void	exec_env(char **env);
char	*get_my_env(char **env, char *name);

/* ----------- exit.c ----------- */
void	exec_exit(char **command);

/* ----------- ft_strtok.c ----------- */
char	*ft_strtok(char *str, char *separators);

/* ----------- signal_handling.c ----------- */
void	signal_handler(int sig);
void	setup_parent_signal(void);
void	setup_child_signal(void);

#endif //MINISHELL_H