/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 15:06:47 by gkehren           #+#    #+#             */
/*   Updated: 2022/07/17 16:43:33 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

/*******INCLUDE*******/

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>

/*******STRUCT*******/

typedef struct s_pipex
{
	char	**env;
	char	*file1;
	int		fd1;
	int		fd2;
	char	*file2;
	char	*cmd1;
	char	*cmd2;
}	t_pipex;

#endif
