/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_pipex_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 14:50:15 by gkehren           #+#    #+#             */
/*   Updated: 2022/08/17 20:03:58 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	parse_arg(t_pipex *pipex, int argc, char **argv, char **env)
{
	int	i;

	i = 0;
	if (argc < 5)
		return (write(2, "\033[31mError\nUsage: \
./pipex <file1> <cmd1> <cmd2> <file2>\n", 57), 1);
	pipex->file1 = argv[1];
	pipex->cmd = malloc(sizeof(t_cmd) * argc - 3);
	while (i < argc - 3)
	{
		pipex->cmd[i].cmd = argv[i + 2];
		i++;
	}
	pipex->file2 = argv[argc - 1];
	pipex->env = env;
	pipex->cmd_count = argc - 3;
	pipex->argc = argc;
	return (0);
}

void	enverror(t_pipex *pipex, int c)
{
	int	i;

	i = 0;
	write(2, "\033[31mError: unset env\n", 23);
	while (i < c + 1)
	{
		freestr(pipex->cmd[i].arg);
		i++;
	}
	free(pipex->cmd);
	exit(EXIT_FAILURE);
}

char	*path_command(t_pipex *pipex, char *cmd, char **env, int c)
{
	char	**paths;
	char	*path;
	int		i;
	char	*part_path;

	i = 0;
	while (ft_strnstr(env[i], "PATH", 4) == 0)
	{
		if (!env[i])
			enverror(pipex, c);
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
		pipex->cmd[i].arg = ft_split(pipex->cmd[i].cmd, ' ');
		if (!pipex->cmd[i].arg[0] || !pipex->cmd[i].arg)
			return (freeall(pipex, i), 1);
		pipex->cmd[i].path = path_command(pipex,
				pipex->cmd[i].arg[0], pipex->env, i);
		if (!pipex->cmd[i].path)
		{
			write(2, "\033[31mError: command not found\n", 31);
			freeall(pipex, i);
			exit(127);
		}
		i++;
	}
	return (0);
}

int	get_command_doc(t_pipex *pipex)
{
	int	i;

	i = 1;
	while (i < pipex->cmd_count)
	{
		pipex->cmd[i].arg = ft_split(pipex->cmd[i].cmd, ' ');
		if (!pipex->cmd[i].arg[0] || !pipex->cmd[i].arg)
			return (freeall(pipex, i), 1);
		pipex->cmd[i].path = path_command(pipex,
				pipex->cmd[i].arg[0], pipex->env, i);
		if (!pipex->cmd[i].path)
		{
			write(2, "\033[31mError: command not found\n", 31);
			freeall(pipex, i);
			exit(127);
		}
		i++;
	}
	return (0);
}
