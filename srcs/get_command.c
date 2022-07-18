/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 17:30:52 by gkehren           #+#    #+#             */
/*   Updated: 2022/07/18 18:18:34 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	*name_command(char *cmd)
{
	char	*name;
	int		i;

	i = 0;
	while (cmd[i] && cmd[i] != ' ')
		i++;
	name = (char *)malloc(sizeof(char) * (i + 1));
	i = 0;
	while (cmd[i] && cmd[i] != ' ')
	{
		name[i] = cmd[i];
		i++;
	}
	name[i + 1] = '\0';
	return (name);
}

char	*arg_command(char *cmd)
{
	char	*arg;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (cmd[i] && cmd[i] != ' ')
		i++;
	while (cmd[i] && cmd[i] == ' ')
		i++;
	arg = (char *)malloc(sizeof(char) * ((ft_strlen(cmd) - i) + 1));
	while (cmd[i])
	{
		arg[j] = cmd[i];
		i++;
		j++;
	}
	return (arg);
}

pid_t	get_path(char *const *c)
{
	pid_t	ch_pid;

	ch_pid = fork();
	if (ch_pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (ch_pid == 0)
	{
		execve(c[0], c, NULL);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else
		return (ch_pid);
}

char	*path_command(char *cmd, char **envp)
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

int	get_command(t_pipex *pipex)
{
	//printf("cmd1 = %s\n", pipex->cmd1.cmd);
	pipex->cmd1.name = name_command(pipex->cmd1.cmd);
	//printf("name = %s\n", pipex->cmd1.name);
	pipex->cmd1.arg = arg_command(pipex->cmd1.cmd);
	//printf("args = %s\n", pipex->cmd1.arg);
	pipex->cmd1.path = path_command(pipex->cmd1.name, pipex->env);
	//printf("path = %s\n", pipex->cmd1.path);
	return (0);
}
