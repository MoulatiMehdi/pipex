/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 22:17:17 by mmoulati          #+#    #+#             */
/*   Updated: 2025/02/04 22:40:56 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

typedef enum e_mode
{
	FILE_WRITE_APPEND = 0,
	FILE_WRITE_TRUNCT = 1,
	FILE_READ = 2,
}		t_mode;

int	t_cmd_exec(char *cmd)
{
	char	**str;

	str = ft_split(cmd, " \n\t");
	execve(str[0], str, NULL);
	ft_split_free(&str);
	perror(str[0]);
	exit(errno);
}

int	t_file_open(char *file, t_mode mode)
{
	int	fd;
	int	o_flags;

	if (mode == FILE_WRITE_TRUNCT)
		fd = open(file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	else if (mode == FILE_WRITE_APPEND)
		fd = open(file, O_CREAT | O_APPEND | O_WRONLY, 0644);
	else if (mode == FILE_READ)
		fd = open(file, O_RDONLY);
	if (fd < 0)
		perror(file);
	else
	{
		if (mode == FILE_READ)
			dup2(fd, STDIN_FILENO);
		else
			dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	return (fd);
}

int	t_pipe_new(int *pipefd)
{
	if (pipe(pipefd) < 0)
	{
		perror("pipe");
		exit(errno);
	}
	return (0);
}

void	t_process_first(char *cmd, char *filename, int pipefd[2])
{
	pid_t	pid;
	int		fd;
	char	**str;

	t_pipe_new(pipefd);
	pid = fork();
	if (pid < 0)
	{
		perror("pipex");
		exit(errno);
	}
	if (pid > 0)
		return ;
	if (filename)
		fd = t_file_open(filename, FILE_READ);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
	close(pipefd[0]);
	t_cmd_exec(cmd);
}

pid_t	t_process_last(char *cmd, char *filename, int fd_in)
{
	pid_t	pid;
	int		fd;
	char	**str;

	pid = fork();
	if (pid < 0)
	{
		perror("pipex");
		exit(errno);
	}
	if (pid > 0)
		return (pid);
	if (filename)
		fd = t_file_open(filename, FILE_WRITE_APPEND);
	dup2(fd_in, STDIN_FILENO);
	close(fd_in);
	t_cmd_exec(cmd);
	return (0);
}

void	t_process_middle(char *cmd, int *fds, int read_fd)
{
	pid_t	pid;

	if (pipe(fds) < 0)
	{
		perror("pipe");
		exit(errno);
	}
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(errno);
	}
	else if (pid == 0)
	{
		dup2(read_fd, STDIN_FILENO);
		dup2(fds[1], STDOUT_FILENO);
		close(read_fd);
		close(fds[1]);
		close(fds[0]);
		t_cmd_exec(cmd);
	}
}

int	t_process_wait(pid_t pid_last, unsigned int n)
{
	int		wstate_last;
	int		wstate;
	pid_t	pid;

	wstate = 0;
	while (n)
	{
		pid = wait(&wstate);
		if (pid == pid_last)
			wstate_last = wstate;
		n--;
	}
	return (WEXITSTATUS(wstate_last));
}

int	main(int argc, char *argv[])
{
	int		fds[2];
	int		read_fd;
	pid_t	pid;
	int		i;

	if (argc < 5)
		return (0);
	t_process_first(argv[2], NULL, fds);
	close(fds[1]);
	read_fd = fds[0];
	i = 3;
	while (i < argc - 2)
	{
		t_process_middle(argv[i], fds, read_fd);
		close(fds[1]);
		close(read_fd);
		read_fd = fds[0];
		i++;
	}
	pid = t_process_last(argv[argc - 2], NULL, read_fd);
	close(read_fd);
	return (t_process_wait(pid, argc - 3));
}
