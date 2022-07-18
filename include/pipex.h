/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 15:06:47 by gkehren           #+#    #+#             */
/*   Updated: 2022/07/18 18:16:40 by gkehren          ###   ########.fr       */
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

typedef struct s_cmd
{
	char		*cmd;
	char		*name;
	char		*path;
	char		*arg;
	char *const	*c;
}	t_cmd;

typedef struct s_pipex
{
	char	**env;
	char	*file1;
	int		fd1;
	int		fd2;
	char	*file2;
	t_cmd	cmd1;
	t_cmd	cmd2;
}	t_pipex;

/*******UTILS*******/

int		first_command(t_pipex *pipex);
int		get_command(t_pipex *pipex);

/*******TOOLS*******/

int		ft_strlen(const char *s);
char	**ft_split(char const *s, char c);
void	*ft_memalloc(size_t size);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);

#endif
