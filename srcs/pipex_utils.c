/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 16:50:59 by gkehren           #+#    #+#             */
/*   Updated: 2022/07/20 14:23:19 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	*path_command(char *cmd, char **env)
{
	char	**paths;
	char	*path;
	int		i;
	char	*part_path;

	i = 0;
	while (ft_strnstr(env[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(env[i] + 5, ':');
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
	int	i;

	pipex->cmd1.arg = ft_split(pipex->cmd1.cmd, ' ');
	pipex->cmd2.arg = ft_split(pipex->cmd2.cmd, ' ');
	pipex->cmd1.path = path_command(pipex->cmd1.arg[0], pipex->env);
	i = -1;
	if (!pipex->cmd1.path)
	{
		while (pipex->cmd1.arg[++i])
			free(pipex->cmd1.arg[i]);
		free(pipex->cmd1.arg);
		error();
	}
	pipex->cmd2.path = path_command(pipex->cmd2.arg[0], pipex->env);
	i = -1;
	if (!pipex->cmd1.path)
	{
		while (pipex->cmd1.arg[++i])
			free(pipex->cmd1.arg[i]);
		free(pipex->cmd1.arg);
		error();
	}
	return (0);
}

void	child_process(t_pipex *pipex)
{
	int	infile;

	infile = open(pipex->file1, O_RDONLY, 0777);
	if (infile == -1)
		error();
	dup2(pipex->fd[1], STDOUT_FILENO);
	close(pipex->fd[0]);
	dup2(infile, STDIN_FILENO);
	if (execve(pipex->cmd1.path, pipex->cmd1.arg, pipex->env) == -1)
		error();
	close(infile);
}

void	parent_process(t_pipex *pipex)
{
	int	outfile;

	outfile = open(pipex->file2, O_TRUNC | O_CREAT | O_RDWR, 0000644);
	if (outfile == -1)
		error();
	dup2(pipex->fd[0], STDIN_FILENO);
	close(pipex->fd[1]);
	dup2(outfile, STDOUT_FILENO);
	if (execve(pipex->cmd2.path, pipex->cmd2.arg, pipex->env) == -1)
		error();
	close(outfile);
}
