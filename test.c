/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 22:17:17 by mmoulati          #+#    #+#             */
/*   Updated: 2025/02/04 12:28:00 by mmoulati         ###   ########.fr       */
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

void	print_pipe(char *name, int *curr)
{
	fprintf(stderr, "%6s:\t in : %d out: %d\n", name, curr[0], curr[1]);
}

void	debug(int *pprev, int *prev, int *curr, int chid)
{
	fprintf(stderr, "Childs %d\n", chid);
	print_pipe("pprev", pprev);
	print_pipe("prev", prev);
	print_pipe("curr", curr);
}

int		g_size = sizeof(g_cmd) / sizeof(g_cmd[0]);

int	main(int argc, char *argv[])
{
	int		i;
	pid_t	pid;
	int		pipes[g_size][2];
	int		j;

	i = 0;
	while (i < g_size - 1)
	{
		pipe(pipes[i]);
		i++;
	}
	i = 0;
	while (i < g_size)
	{
		pid = fork();
		if (i < 0)
		{
			perror("fork");
			exit(errno);
		}
		else if (pid == 0)
		{
			if (i != 0)
				dup2(pipes[i - 1][0], STDIN_FILENO);
			if (i != g_size - 1)
				dup2(pipes[i][1], STDOUT_FILENO);
			j = 0;
			while (j < g_size - 1)
			{
				close(pipes[j][0]);
				close(pipes[j][1]);
				j++;
			}
			execve(g_cmd[i][0], g_cmd[i], 0);
			perror("execve");
			exit(errno);
		}
		i++;
	}
	i = 0;
	while (i < g_size - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
	i = 0;
	while (i < g_size)
		wait(NULL);
	return (0);
}
