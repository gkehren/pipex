/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_other.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 16:18:30 by gkehren           #+#    #+#             */
/*   Updated: 2022/08/15 16:22:23 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	freestr(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
}

void	error(t_pipex *pipex)
{
	free(pipex->cmd1.path);
	free(pipex->cmd2.path);
	freestr(pipex->cmd1.arg);
	freestr(pipex->cmd2.arg);
	perror("\033[31mError");
	exit(EXIT_FAILURE);
}

void	waitforall(void)
{
	int		status;
	int		n;
	pid_t	pid;

	n = 0;
	while (n < 2)
	{
		pid = wait(&status);
		n++;
	}
}

void	job(t_pipex *pipex)
{
	dup2(pipex->fd[1], STDOUT_FILENO);
	close(pipex->fd[0]);
}
