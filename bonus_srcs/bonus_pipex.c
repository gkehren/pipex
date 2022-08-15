/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 14:50:10 by gkehren           #+#    #+#             */
/*   Updated: 2022/08/15 16:52:32 by gkehren          ###   ########.fr       */
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
	pipex->file2 = argv[4];
	pipex->env = env;
	pipex->cmd_count = argc - 3;
	return (0);
}

int	exec_all(t_pipex *pipex)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (i < pipex->cmd_count)
	{
		pid = fork();
		if (pid == -1)
			error(pipex);
		else if (pid == 0)
			job(pipex);
		else
			parent_process(pipex);
		i++;
	}
	waitforall();
	return (0);
}

int	exec_command(t_pipex *pipex)
{
	pid_t		child;

	child = fork();
	if (child == -1)
		error(pipex);
	if (child == 0)
		child_process(pipex);
	waitpid(child, NULL, 0);
	exec_all(pipex);
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_pipex	pipex;

	if (pipe(pipex.fd) == -1)
	{
		perror("\033[31mError");
		exit(EXIT_FAILURE);
	}
	if (parse_arg(&pipex, argc, argv, env) == 1)
		return (1);
	if (get_command(&pipex) == 1)
		return (write(2, "\033[31mError\nUsage: \
./pipex <file1> <cmd1> <cmd2> <file2>\n", 57), 1);
	if (exec_command(&pipex) == 1)
		return (1);
	//free(pipex.cmd1.path);
	//free(pipex.cmd2.path);
	//freestr(pipex.cmd1.arg);
	//freestr(pipex.cmd2.arg);
	// need to free all the struct cmd[].path and arg
	free(pipex.cmd);
	return (0);
}
