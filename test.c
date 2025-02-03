/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 22:17:17 by mmoulati          #+#    #+#             */
/*   Updated: 2025/02/04 00:34:00 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

char	*g_cmd[][4] = {
	{"/bin/cat", NULL},
	{"/bin/cat", "-e", NULL},
	{"/bin/grep", "_", NULL},
};

int		g_size = sizeof(g_cmd) / sizeof(g_cmd[0]);

int	main(int argc, char *argv[])
{
	int		i;
	int		fd_in;
	int		pipefd[2];
	pid_t	pid;

	i = 0;
	fd_in = dup(STDIN_FILENO);
	while (i < g_size)
	{
		if (pipe(pipefd) == -1)
		{
			perror("pipe");
			return (errno);
		}
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			return (errno);
		}
		else if (pid == 0)
		{
			if (i > 0)
			{
				if (dup2(fd_in, STDIN_FILENO) < 0)
				{
					fprintf(stderr, "Child %d : ", i);
					perror("dup2 in");
					fprintf(stderr, "%d %d\n", fd_in, STDIN_FILENO);
					return (errno);
				}
			}
			else
			{
				if (close(pipefd[0]) < 0)
				{
					perror("close");
				}
			}
			if (i < g_size - 1)
			{
				if (dup2(pipefd[1], STDOUT_FILENO) < 0)
				{
					fprintf(stderr, "Child %d : ", i);
					perror("dup2 out");
					fprintf(stderr, "%d %d\n", pipefd[1], STDOUT_FILENO);
					return (errno);
				}
				close(pipefd[1]);
			}
			fprintf(stderr, "Childs %d\nfd_in : %d pipefd[0]:%d pipefd[1]:%d\n",
				i, fd_in, pipefd[0], pipefd[1]);
			execve(g_cmd[i][0], g_cmd[i], NULL);
			close(fd_in);
			perror("execve");
			exit(errno);
		}
		close(pipefd[1]);
		close(fd_in);
		fd_in = pipefd[0];
		i++;
	}
	close(fd_in);
	i = 0;
	while (i < g_size)
	{
		wait(NULL);
		i++;
	}
	return (EXIT_SUCCESS);
}
