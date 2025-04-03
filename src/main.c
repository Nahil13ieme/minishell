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

t_btree	*set_root(t_btree *root, char c)
{
	static t_btree	*global_tree = NULL;

	if (c == 's')
	{
		if (global_tree)
			free_tree(global_tree);
		global_tree = root;
	}
	else if (c == 'g')
	{
		if (global_tree)
			return (global_tree);
		else
			return (NULL);
	}
	else if (c == 'f')
	{
		free_tree(global_tree);
		global_tree = NULL;
	}
	return (NULL);
}

void	process_line(char *line, char **envp)
{
	t_token_stream	*ts;

	if (line[0] != '\0')
	{
		add_history(line);
		ts = tokenize_input(line, envp);
		if (!validate_token_sequence(ts))
		{
			free_token_stream(ts);
			return ;
		}
		set_root(parse_input(ts), 's');
		free_token_stream(ts);
		if (set_root(NULL, 'g'))
		{
			execute_tree(set_root(NULL, 'g'), envp);
			set_exit_code(set_root(NULL, 'g')->status);
			set_root(NULL, 'f');
		}
		else
			printf("Error parsing input\n");
	}
}

int	main(int ac, char **av, char **env)
{
	char	*line;
	char	*prompt;

	(void)ac;
	(void)av;
	using_history();
	get_env(env);
	set_exit_code(0);
	while (1)
	{
		prompt = make_prompt();
		line = readline(prompt);
		if (prompt)
			free(prompt);
		if (!line)
			break ;
		process_line(line, sim_glob(NULL, 'g'));
		free(line);
	}
	return (0);
}
