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

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	char	*line;
	char	*prompt;
	
	env[0] = "SHELL=";
	env[0] = ft_strjoin(env[0], getcwd(NULL, 0));
	using_history();
	while (1)
	{
		prompt = ft_strjoin(ft_strjoin(GREEN, get_username()), "@minishell" WHITE ":" BLUE);
		prompt = ft_strjoin(prompt, getcwd(NULL, 0));
		prompt = ft_strjoin(prompt, " " WHITE);
		line = readline(prompt);
		if (!line)
			break ;
		if (line[0] != '\0')
			add_history(line);
		parse_line(line, env);
		free(prompt);
		free(line);
	}
	return (0);
}
