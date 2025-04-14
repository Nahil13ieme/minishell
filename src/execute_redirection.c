/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 09:56:35 by nbenhami          #+#    #+#             */
/*   Updated: 2025/04/14 20:18:07 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "minishell.h"

/**
 * @brief Vérifie si le fichier est valide pour l'ouverture
 * @param file Le nom du fichier à vérifier
 * @return 0 si valide, 1 si invalide
 */
static int	check_file_validity(char *file, t_btree *node)
{
	if (ft_strlen(file) >= 256)
	{
		ft_fprintf("minishell: %s: File name too long\n", file);
		node->status = 1;
		return (1);
	}
	else if (check_dir_file(file) == 1)
	{
		node->status = 1;
		return (1);
	}
	return (0);
}

/**
 * @brief Ouvre un fichier avec les flags appropriés
 * @return Le descripteur de fichier ou -1 en cas d'erreur
 */
static int	open_file(char *file, int oflags, t_btree *node)
{
	int	new_fd;

	new_fd = open(file, oflags, 0644);
	if (new_fd == -1)
	{
		if (errno == EACCES)
			ft_fprintf("minishell: %s: Permission denied\n", file);
		else if (errno == ENOENT)
			ft_fprintf("minishell: %s: No such file or directory\n", file);
		node->status = 1;
	}
	return (new_fd);
}

/**
 * @brief Gère un nœud de redirection
 * @return 0 si OK, -1 si erreur
 */
static int	handle_redirection_node(t_btree *node, int *fd_in, int *fd_out)
{
	int	std;
	int	oflags;
	int	new_fd;

	std = get_std(node);
	oflags = get_oflags(node->type);
	if (node->type == NODE_HEREDOC)
	{
		apply_heredoc(node, 0);
		*fd_in = -1;
		return (0);
	}
	if (check_file_validity(node->file, node))
		return (-1);
	new_fd = open_file(node->file, oflags, node);
	if (new_fd == -1)
		return (-1);
	check_std(std, fd_in, new_fd, fd_out);
	return (0);
}

/**
 * @brief Applique les redirections pour les descripteurs de fichiers
 * @return 0 si réussi, -1 si échoué
 */
static int	apply_redirections(int fd_in, int fd_out)
{
	if (fd_in >= 0)
	{
		if (dup2(fd_in, STDIN_FILENO) == -1)
			exit_error("dup2");
		close(fd_in);
	}
	if (fd_out >= 0)
	{
		if (dup2(fd_out, STDOUT_FILENO) == -1)
			exit_error("dup2");
		close(fd_out);
	}
	return (0);
}

/**
 * @brief Ouvre les descripteurs de fichiers pour les redirections
 * @param count Nombre de nœuds
 * @param nodes Tableau de nœuds
 * @return 0 si réussi, -1 si échoué
 */
int	open_fd(int count, t_btree *nodes[100])
{
	int	i;
	int	fd_in;
	int	fd_out;
	int	result;

	i = count - 1;
	fd_in = -1;
	fd_out = -1;
	while (i >= 0)
	{
		result = handle_redirection_node(nodes[i], &fd_in, &fd_out);
		if (result == -1)
		{
			if (fd_in != -1)
				close(fd_in);
			if (fd_out != -1)
				close(fd_out);
			return (-1);
		}
		i--;
	}
	return (apply_redirections(fd_in, fd_out));
}
