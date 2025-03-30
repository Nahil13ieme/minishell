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

void	print_tree(t_btree tree)
{
	int	i;

	i = 0;
	if (tree.left)
		print_tree(*tree.left);
	if (tree.cmd)
	{
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

void	process_line(char *line, char **envp)
{
	t_token_stream	*ts;
	t_btree			*root;

	if (line[0] != '\0')
	{
		add_history(line);
		ts = tokenize_input(line, envp);
		if (!validate_token_sequence(ts))
		{
			free_token_stream(ts);
			return ;
		}
		root = parse_input(ts);
		free_token_stream(ts);
		if (root)
		{
			execute_tree(root, envp);
			free_tree(root);
			root = NULL;
		}
		else
			printf("Error parsing input\n");
	}
}

int	main(int ac, char **av, char **env)
{
	char	*line;
	char	*prompt;
	char	**envp;

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
		process_line(line, envp);
		free(line);
	}
	return (0);
}
