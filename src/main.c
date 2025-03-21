/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 14:19:36 by nbenhami          #+#    #+#             */
/*   Updated: 2025/03/07 14:19:36 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_username(void)
{
	char	*name;

	name = getenv("USERNAME");
	if (!name)
	{
		name = getenv("USER");
		if (!name)
		{
			name = getenv("LOGNAME");
			if (!name)
			{
				perror("couldnt retrieve username");
				name = "NULL";
			}
		}
	}
	return (name);
}

char	*make_prompt(void)
{
	char	*user;
	char	*cur_path;
	char	*tmp;
	char	*prompt;

	prompt = GREEN;
	user = get_username();
	user = ft_strjoin(user, "@minishell" WHITE ":" BLUE);
	prompt = ft_strjoin(prompt, user);
	free(user);
	cur_path = getcwd(NULL, 0);
	if (cur_path == NULL)
		cur_path = ft_strdup("??");
	tmp = prompt;
	prompt = ft_strjoin(prompt, cur_path);
	free(tmp);
	free(cur_path);
	tmp = prompt;
	prompt = ft_strjoin(prompt, WHITE "$ ");
	free(tmp);
	return (prompt);
}

void	print_token_stream(t_token_stream *ts)
{
	int	i;

	i = 0;
	while (i < ts->size)
	{
		t_token_type expression = ts->tokens[i]->type;
		printf("Token %d: Type: ", i);
		switch (expression)
		{
		case TOKEN_COMMAND:
			printf("COMMAND, Value: %s\n", ts->tokens[i]->value);
			break;
		case TOKEN_PIPE:
			printf("PIPE, Value: %s\n", ts->tokens[i]->value);
			break;
		case TOKEN_AND:
			printf("AND, Value: %s\n", ts->tokens[i]->value);
			break;
		case TOKEN_OR:
			printf("OR, Value: %s\n", ts->tokens[i]->value);
			break;
		case TOKEN_SEMICOLON:
			printf("SEMICOLON, Value: %s\n", ts->tokens[i]->value);
			break;
		case TOKEN_REDIR_IN:
			printf("REDIR_IN, Value: %s\n", ts->tokens[i]->value);
			break;
		case TOKEN_REDIR_OUT:
			printf("REDIR_OUT, Value: %s\n", ts->tokens[i]->value);
			break;
		case TOKEN_HEREDOC:
			printf("HEREDOC, Value: %s\n", ts->tokens[i]->value);
			break;
		case TOKEN_APPEND:
			printf("APPEND, Value: %s\n", ts->tokens[i]->value);
			break;
		case TOKEN_WORD:
			printf("WORD, Value: %s\n", ts->tokens[i]->value);
			break;
		case TOKEN_QUOTED:
			printf("QUOTED, Value: %s\n", ts->tokens[i]->value);
			break;
		default:
			break;
		}
		i++;
	}
}

void	print_tree(t_btree tree)
{
	if (tree.left)
		print_tree(*tree.left);
	if (tree.cmd)
	{
		int i = 0;
		while (tree.cmd[i])
		{
			printf("%s ", tree.cmd[i]);
			i++;
		}
		printf("\n");
	}
	if (tree.right)
		print_tree(*tree.right);
}

int	main(int ac, char **av, char **env)
{
	char			*line;
	char			*prompt;
	char	**envp;
	t_token_stream	*ts;

	(void)ac;
	(void)av;
	envp = env;
	using_history();
	while (1)
	{
		prompt = make_prompt();
		line = readline(prompt);
		if (prompt)
			free(prompt);
		if (!line)
			break ;
		if (line[0] != '\0')
		{
			add_history(line);
			ts = tokenize_input(line, envp);
			if (!validate_token_sequence(ts))
			{
				free(line);
				continue ;
			}
			print_token_stream(ts);
			t_btree	*root = parse_input(ts);
			if (root)
			{
				execute_tree(root, envp);
				//free_tree(root);
			}
			else
			{
				printf("Error parsing input\n");
			}
			free_token_stream(ts);
		}
		free(line);
	}
	return (0);
}
