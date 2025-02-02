/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 17:59:16 by mmoulati          #+#    #+#             */
/*   Updated: 2025/02/02 11:50:34 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

char	*g_cmd[][4] = {
	{"/bin/cat", NULL},
	{"/bin/grep", "1", NULL},
};

int	main(int argc, char *argv[])
{
	pid_t	pid;
	int		size;
	int		fd_in;
	int		fd_out;
	int		**pipes;
	pid_t	last_pid;
	int		wstate;

	wstate = 0;
	size = sizeof(g_cmd) / sizeof(g_cmd[0]);
	// fd_out = open("output.txt", O_WRONLY | O_TRUNC | O_CREAT, 0644);
	// fd_in = open("input.txt", O_RDONLY);
	fd_out = dup(STDOUT_FILENO);
	fd_in = dup(STDIN_FILENO);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	pipes = t_pipes_new(size - 1);
	if (pipes == NULL)
	{
		perror("pipe");
		exit(errno);
	}
	for (int i = 0; i < size; i++)
	{
		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			exit(errno);
		}
		else if (pid == 0)
		{
			t_pipes_set(pipes, i);
			if (i == 0)
				dup2(fd_in, STDIN_FILENO);
			if (i == size - 1)
				dup2(fd_out, STDOUT_FILENO);
			close(fd_out);
			close(fd_in);
			execve(g_cmd[i][0], g_cmd[i], NULL);
			fprintf(stderr, "child %d: %s: %s\n", i, g_cmd[i][0],
				strerror(errno));
			t_pipes_close(pipes);
			exit(errno);
		}
		else if (i == size - 1)
			last_pid = pid;
	}
	t_pipes_close(pipes);
	for (int i = 0; i < size - 1; i++)
		wait(NULL);
	waitpid(last_pid, &wstate, 0);
	t_pipes_free(&pipes);
	return (WEXITSTATUS(wstate));
}
