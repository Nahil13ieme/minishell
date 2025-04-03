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
