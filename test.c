/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 22:17:17 by mmoulati          #+#    #+#             */
/*   Updated: 2025/02/04 20:56:09 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void	t_process_first(char *cmd, char *filename, int fds[2])
{
	pid_t	pid;
	int		read_fd;
	char	**strs;

	pid = fork();
	if (pid > 0)
		return ;
	if (pid < 0)
	{
		perror("fork");
		exit(errno);
	}
	if (filename)
	{
		read_fd = open(filename, O_RDONLY);
		if (read_fd < 0)
		{
			perror(filename);
			exit(errno);
		}
		dup2(read_fd, STDIN_FILENO);
		close(read_fd);
	}
	dup2(fds[1], STDOUT_FILENO);
	close(fds[1]);
	close(fds[0]);
	strs = ft_split(cmd, " \n\t");
	execve(strs[0], strs, NULL);
	perror(strs[0]);
	ft_split_free(&strs);
	exit(errno);
}

void	t_process_last(char *cmd, char *filename, int read_in)
{
	pid_t	pid;
	int		out_fd;
	char	**strs;

	pid = fork();
	if (pid > 0)
		return ;
	if (pid < 0)
	{
		perror("fork");
		exit(errno);
	}
	dup2(read_in, STDIN_FILENO);
	close(read_in);
	if (filename)
	{
		out_fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC);
		if (out_fd < 0)
		{
			perror(filename);
			exit(errno);
		}
		dup2(out_fd, STDIN_FILENO);
		close(out_fd);
	}
	strs = ft_split(cmd, " \n\t");
	execve(strs[0], strs, NULL);
	perror(strs[0]);
	ft_split_free(&strs);
	exit(errno);
}
int	main(int argc, char *argv[])
{
	int		fds[2];
	int		read_fd;
	pid_t	pid;
	int		i;
	char	**strs;

	i = 1;
	while (i < argc)
	{
		if (i < argc - 1 && pipe(fds) < 0)
		{
			perror("pipe");
			exit(errno);
		}
		pid = fork();
		if (pid < 0)
		{
			perror("pipe");
			exit(errno);
		}
		else if (pid == 0)
		{
			if (i != 0)
			{
				dup2(read_fd, STDIN_FILENO);
				close(read_fd);
			}
			if (i != argc - 1)
			{
				dup2(fds[1], STDOUT_FILENO);
			}
			close(fds[1]);
			close(fds[0]);
			strs = ft_split(argv[i], " \n\t");
			execve(strs[0], strs, NULL);
			perror(strs[0]);
			ft_split_free(&strs);
			exit(errno);
		}
		close(fds[1]);
		close(read_fd);
		read_fd = fds[0];
		i++;
	}
	close(read_fd);
	close(fds[0]);
	close(fds[1]);
	while (wait(NULL) > 0)
		; //////////////////////////////until false
	return (EXIT_SUCCESS);
}
