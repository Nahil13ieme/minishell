#include "../include/minishell.h"

static void	free_paths(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

static char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	int		i;
	char	*part_path;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
			return (free_paths(paths), path);
		free(path);
		i++;
	}
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	return (0);
}

static void	path_not_found(char **cmd)
{
	int	i;

	i = 0;
	printf("%s: command not found\n", cmd[0]);
	while (cmd[++i])
		free(cmd[i]);
	free(cmd);
}


int	execute_path(char **cmd, char **envp)
{
	char	*path;
	pid_t	pid1;
	int		ret;

	ret = 0;
	path = find_path(cmd[0], envp);
	if (!path)
		path_not_found(cmd);
	pid1 = fork();
	if (pid1 == -1)
		exit(EXIT_FAILURE);
	if (pid1 == 0)
	{
		if (execve(path, cmd, envp) == -1)
			exit(EXIT_FAILURE);
	}
	else if (pid1 > 0)
		waitpid(pid1, &ret, 0);
	else if (pid1 < 0)
		exit(EXIT_FAILURE);
	free(path);
	return (ret / 256);
}
