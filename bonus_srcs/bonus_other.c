/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_other.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 16:18:30 by gkehren           #+#    #+#             */
/*   Updated: 2022/08/15 19:52:39 by gkehren          ###   ########.fr       */
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
	//free(pipex->cmd1.path);
	//free(pipex->cmd2.path);
	//freestr(pipex->cmd1.arg);
	//freestr(pipex->cmd2.arg);
	(void)pipex;
	perror("\033[31mError");
	exit(EXIT_FAILURE);
}
