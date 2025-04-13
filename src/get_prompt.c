/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-saut <tle-saut@student.42perpignan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 14:23:40 by tle-saut          #+#    #+#             */
/*   Updated: 2025/04/13 15:12:47 by tle-saut         ###   ########.fr       */
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
				name = "????";
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
