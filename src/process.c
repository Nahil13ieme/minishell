/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 14:26:03 by tle-saut          #+#    #+#             */
/*   Updated: 2025/04/09 16:14:00 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	process_line(char *line)
{
	t_token_stream	*ts;

	if (line[0])
	{
		add_history(line);
		ts = tokenize_input(line);
		if (!validate_token_sequence(ts))
		{
			set_exit_code(2);
			free_token_stream(ts);
			return ;
		}
		set_root(parse_input(ts), 's');
		free_token_stream(ts);
		if (set_root(NULL, 'g'))
		{
			execute_tree(set_root(NULL, 'g'));
			set_exit_code(set_root(NULL, 'g')->status);
			set_root(NULL, 'f');
		}
		else
			ft_fprintf("Error parsing input\n");
	}
}
