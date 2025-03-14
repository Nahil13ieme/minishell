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
	{
			cur_path = ft_strdup("??");
	}
	tmp = prompt;
	prompt = ft_strjoin(prompt, cur_path);
	free(tmp);
	free(cur_path);
	tmp = prompt;
	prompt = ft_strjoin(prompt, WHITE "$ ");
	free(tmp);
	return (prompt);
}

int	main(int ac, char **av, char **env)
{
	char	*line;
	char	*prompt;
	char	**envp;

	(void)ac;
	(void)av;
	envp = env;
	setup_parent_signal();
	using_history();
	while (1)
	{
		prompt = make_prompt();
		line = readline(prompt);
		free(prompt);
		if (!line)
			break ;
		if (line[0] != '\0')
		{
			add_history(line);
			parse_line(line, &envp);
		}
		free(line);
	}
	return (0);
}
