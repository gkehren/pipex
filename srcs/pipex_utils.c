/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 16:50:59 by gkehren           #+#    #+#             */
/*   Updated: 2022/07/18 18:20:19 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

pid_t	exec_command(char *const *c, char **env)
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
		execve(c[0], c, env);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else
		return (ch_pid);
	return (0);
}

int	first_command(t_pipex *pipex)
{
	pid_t		child;
	int			wstatus;
	char *const	c[3] = {pipex->cmd1.path, pipex->cmd1.arg, NULL};

	child = exec_command(c, pipex->env);
	if (waitpid(child, &wstatus, WUNTRACED | WCONTINUED) == -1)
	{
		perror("waitpid");
		exit(EXIT_FAILURE);
	}
	return (0);
}
