/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 14:26:03 by tle-saut          #+#    #+#             */
/*   Updated: 2025/04/03 18:11:05 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
