/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 15:06:47 by gkehren           #+#    #+#             */
/*   Updated: 2022/08/16 04:21:59 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

/*******INCLUDE*******/

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

/*******STRUCT*******/

typedef struct s_cmd
{
	char		*cmd;
	char		*path;
	char		**arg;
	char *const	*c;
}	t_cmd;

typedef struct s_pipex
{
	int		argc;
	char	**env;
	char	*file1;
	int		fd1;
	int		fd2;
	int		fd[2];
	char	*file2;
	int		cmd_count;
	t_cmd	*cmd;
	t_cmd	cmd1;
	t_cmd	cmd2;
}	t_pipex;

/*******UTILS*******/

void	parent_process(t_pipex *pipex);
void	child_process(t_pipex *pipex);
void	child_bonus(t_pipex *pipex, int i);
int		exec_command(t_pipex *pipex);
int		get_command(t_pipex *pipex);
void	freestr(char **s);
void	error(t_pipex *pipex);

/*******TOOLS*******/

int		get_next_line(char **line);
int		ft_strlen(const char *s);
char	**ft_split(char const *s, char c);
void	*ft_memalloc(size_t size);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

#endif
