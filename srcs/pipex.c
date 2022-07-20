/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 14:57:37 by gkehren           #+#    #+#             */
/*   Updated: 2022/07/20 14:13:13 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	parse_arg(t_pipex *pipex, int argc, char **argv, char **env)
{
	if (argc != 5)
		return (write(1, "\033[31mError\nUsage: \
./pipex <file1> <cmd1> <cmd2> <file2>\n", 57), 1);
	pipex->file1 = argv[1];
	pipex->cmd1.cmd = argv[2];
	pipex->cmd2.cmd = argv[3];
	pipex->file2 = argv[4];
	pipex->env = env;
	return (0);
}

void	error(void)
{
	perror("\033[31mError");
	exit(EXIT_FAILURE);
}

int	exec_command(t_pipex *pipex)
{
	pid_t		child;

	child = fork();
	if (child == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (child == 0)
		child_process(pipex);
	waitpid(child, NULL, 0);
	parent_process(pipex);
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_pipex	pipex;

	if (pipe(pipex.fd) == -1)
		error();
	if (parse_arg(&pipex, argc, argv, env) == 1)
		return (0);
	if (get_command(&pipex) == 1)
		return (0);
	if (exec_command(&pipex) == 1)
		return (0);
	printf("TEST\n");
	return (0);
}
