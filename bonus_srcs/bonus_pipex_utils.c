/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_pipex_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 14:50:15 by gkehren           #+#    #+#             */
/*   Updated: 2022/08/15 16:47:44 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	enverror(t_pipex *pipex)
{
	write(2, "\033[31mError: unset env\n", 23);
	freestr(pipex->cmd1.arg);
	freestr(pipex->cmd2.arg);
	exit(EXIT_FAILURE);
}

char	*path_command(t_pipex *pipex, char *cmd, char **env)
{
	char	**paths;
	char	*path;
	int		i;
	char	*part_path;

	i = 0;
	while (ft_strnstr(env[i], "PATH", 4) == 0)
	{
		if (!env[i])
			enverror(pipex);
		i++;
	}
	paths = ft_split(env[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
			return (freestr(paths), path);
		free(path);
		i++;
	}
	return (freestr(paths), NULL);
}

int	get_command(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->cmd_count)
	{
		pipex->cmd[i].arg = ft_split(pipex->cmd[0].cmd, ' ');
		if (!pipex->cmd[i].arg[0] || !pipex->cmd[i].arg)
			return (freestr(pipex->cmd[i].arg), 1);
		pipex->cmd[i].path = path_command(pipex, pipex->cmd[i].arg[0], pipex->env);
		if (!pipex->cmd[i].path)
		{
			freestr(pipex->cmd1.arg);
			freestr(pipex->cmd2.arg);
			write(2, "\033[31mError: command not found\n", 31);
			exit(127);
		}
		i++;
	}
	return (0);
}

void	child_process(t_pipex *pipex)
{
	int	infile;

	infile = open(pipex->file1, O_RDONLY, 0777);
	if (infile == -1)
		error(pipex);
	dup2(pipex->fd[1], STDOUT_FILENO);
	close(pipex->fd[0]);
	dup2(infile, STDIN_FILENO);
	if (execve(pipex->cmd[0].path, pipex->cmd[0].arg, pipex->env) == -1)
		error(pipex);
	close(infile);
}

void	parent_process(t_pipex *pipex)
{
	int	outfile;

	outfile = open(pipex->file2, O_TRUNC | O_CREAT | O_RDWR, 0000644);
	if (outfile == -1)
		error(pipex);
	dup2(pipex->fd[0], STDIN_FILENO);
	close(pipex->fd[1]);
	dup2(outfile, STDOUT_FILENO);
	if (execve(pipex->cmd[pipex->cmd_count - 1].path, pipex->cmd[pipex->cmd_count - 1].arg, pipex->env) == -1)
		error(pipex);
	close(outfile);
}
