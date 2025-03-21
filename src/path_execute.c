#include "../include/minishell.h"


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
			return (path);
		free(path);
		i++;
	}
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	return (0);
}

int	execute_path(char **cmd, char **envp)
{
	int		i;
	char	*path;
	pid_t	pid1;
	int		ret;

	i = -1;
	ret = 0;
	path = find_path(cmd[0], envp);
	if (!path)
	{
		while (cmd[++i])
		free(cmd[i]);
		free(cmd);
		//error();
	}
	pid1 = fork();
	if (pid1 == -1)
		exit(EXIT_FAILURE);
	if (pid1 == 0)
	{
		if (execve(path, cmd, envp) == -1)
		exit(EXIT_FAILURE);
		//error();
	}
	else if (pid1 > 0)
		waitpid(pid1, &ret, 0);
	else if (pid1 < 0)
		exit(EXIT_FAILURE);
	free(path);
	return (ret / 256);
}
