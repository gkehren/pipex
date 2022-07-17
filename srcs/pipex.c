/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 14:57:37 by gkehren           #+#    #+#             */
/*   Updated: 2022/07/17 16:49:01 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

pid_t	create_file(char *const *c)
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

int	get_file(t_pipex *pipex)
{
	pid_t		child;
	int			wstatus;
	int			fd1;
	int			fd2;
	char *const	c[3] = {"/usr/bin/touch", pipex->file2, NULL};

	fd2 = open(pipex->file2, O_RDWR);
	if (fd2 == -1)
	{
		child = create_file(c);
		if (waitpid(child, &wstatus, WUNTRACED | WCONTINUED) == -1)
		{
			perror("waitpid");
			exit(EXIT_FAILURE);
		}
	}
	fd1 = open(pipex->file1, O_RDWR);
	if (fd1 == -1)
		return (1);
	return (0);
}

int	parse_arg(t_pipex *pipex, int argc, char **argv, char **env)
{
	if (argc != 5)
		return (write(1, "Error\n - Fill all the arguments\n", 33), 1);
	pipex->file1 = argv[1];
	pipex->cmd1 = argv[2];
	pipex->cmd2 = argv[3];
	pipex->file2 = argv[4];
	pipex->env = env;
	if (get_file(pipex) == 1)
		return (write(1, "Error\n - No such file or directory\n", 36), 1);
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_pipex	pipex;

	if (parse_arg(&pipex, argc, argv, env) == 1)
		return (0);
	printf("%s\n%s\n%s\n%s\n", pipex.file1, pipex.cmd1, pipex.cmd2, pipex.file2);
	return (0);
}
