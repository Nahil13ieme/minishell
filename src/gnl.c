/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-saut <tle-saut@student.42perpignan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 13:29:01 by tle-saut          #+#    #+#             */
/*   Updated: 2025/04/13 13:35:24 by tle-saut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_strjoinfree(char **s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*dest;

	i = 0;
	j = 0;
	dest = malloc(sizeof(char) * (ft_strlen(*s1) + ft_strlen(s2) + 1));
	if (!dest)
		return (NULL);
	while ((*s1)[i])
	{
		dest[i] = (*s1)[i];
		i++;
	}
	while (s2[j])
	{
		dest[i + j] = s2[j];
		j++;
	}
	dest[i + j] = '\0';
	free(*s1);
	return (dest);
}

char	*ft_if(char **remaining, char **line)
{
	char	*temp;
	char	*newline;

	newline = ft_strchr(*remaining, '\n');
	if (newline)
	{
		*line = ft_substr(*remaining, 0, newline - *remaining + 1);
		temp = ft_strdup(newline + 1);
		free(*remaining);
		*remaining = temp;
	}
	else
	{
		*line = ft_strdup(*remaining);
		free(*remaining);
		*remaining = NULL;
	}
	return (*line);
}

char	*get_next_line(int fd)
{
	static char	*remaining = NULL;
	char		buffer[BUFFER_SIZE + 1];
	static char	*line = NULL;
	int			bytes_read;

	while (1)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(remaining), remaining = NULL, NULL);
		buffer[bytes_read] = 0;
		if (remaining)
			remaining = ft_strjoinfree(&remaining, buffer);
		else
			remaining = ft_strdup(buffer);
		if (ft_strchr(remaining, '\n') || bytes_read == 0)
			break ;
	}
	if ((ft_strlen(remaining)) > 0)
	{
		ft_if(&remaining, &line);
		return (line);
	}
	else
		return (free(remaining), remaining = NULL, line = NULL, NULL);
}
