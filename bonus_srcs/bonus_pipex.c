/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 14:50:10 by gkehren           #+#    #+#             */
/*   Updated: 2022/08/17 02:27:33 by gkehren          ###   ########.fr       */
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

void	child_bonus(t_pipex *pipex, int i)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		error(pipex);
	pid = fork();
	if (pid == -1)
		error(pipex);
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		if (execve(pipex->cmd[i].path, pipex->cmd[i].arg, pipex->env) == -1)
			error(pipex);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
}

int	exec_command(t_pipex *pipex)
{
	int	infile;
	int	outfile;
	int	i;

	i = 0;
	infile = open(pipex->file1, O_RDONLY, 0777);
	if (infile == -1)
		error(pipex);
	outfile = open(pipex->file2, O_TRUNC | O_CREAT | O_RDWR, 0000644);
	if (outfile == -1)
		error(pipex);
	dup2(infile, STDIN_FILENO);
	while (i < pipex->cmd_count - 1)
		child_bonus(pipex, i++);
	dup2(outfile, STDOUT_FILENO);
	if (execve(pipex->cmd[pipex->cmd_count - 1].path, pipex->cmd[pipex->cmd_count - 1].arg, pipex->env) == -1)
		error(pipex);
	return (0);
}

void	exec_here_doc(char *limiter, int argc, t_pipex *pipex)
{
	pid_t	reader;
	int		fd[2];
	char	*line;

	if (argc < 6)
	{
		write(2, "\033[31mError\nUsage: \
./pipex <file1> <cmd1> <cmd2> <file2>\n", 57);
		error(pipex);
	}
	if (pipe(fd) == -1)
		error(pipex);
	reader = fork();
	if (reader == 0)
	{
		close(fd[0]);
		while (get_next_line(&line))
		{
			if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
				exit(EXIT_SUCCESS);
			write(fd[1], line, ft_strlen(line));
		}
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		wait(NULL);
	}
}

void	here_doc(int argc, char **argv, t_pipex *pipex)
{
	int	outfile;
	int	i;

	i = 1;
	outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0777);
	exec_here_doc(argv[2], argc, pipex);
	while (i < argc - 4)
		child_bonus(pipex, i++);
	dup2(outfile, STDOUT_FILENO);
	if (execve(pipex->cmd[pipex->cmd_count - 1].path, pipex->cmd[pipex->cmd_count - 1].arg, pipex->env) == -1)
		error(pipex);
}

int	main(int argc, char **argv, char **env)
{
	t_pipex	pipex;

	if (parse_arg(&pipex, argc, argv, env) == 1)
		return (1);
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		get_command_doc(&pipex);
		here_doc(argc, argv, &pipex);
	}
	//int	i = 0;
	//while (i < pipex.cmd_count)
	//{
	//	printf("cmd%d: %s\n", i, pipex.cmd[i].cmd);
	//	i++;
	//}
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
	//free(pipex.cmd);
	return (0);
}
