/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 16:51:22 by mmoulati          #+#    #+#             */
/*   Updated: 2025/02/03 18:45:14 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"
#include <stdio.h>

extern char	*g_cmd[][4];

pid_t	t_process_childs(int **pipes, int *fds, unsigned int size)
{
	pid_t	pid;
	int		i;

	i = 0;
	while (i < size)
	{
		pid = fork();
		if (pid < 0)
			return (-1);
		if (pid == 0)
		{
			t_pipes_set(pipes, i);
			if (i == 0)
				dup2(fds[0], STDIN_FILENO);
			if (i == size - 1)
				dup2(fds[1], STDOUT_FILENO);
			t_fds_close(fds);
			execve(g_cmd[i][0], g_cmd[i], NULL);
			t_pipes_close(pipes);
			perror(SHELL_NAME);
			exit(errno);
		}
		i++;
	}
	return (pid);
}

int	t_process_wait(pid_t last_pid, unsigned int size)
{
	pid_t	pid;
	int		wstate_last;
	int		wstate;
	int		i;

	i = 0;
	wstate_last = 0;
	while (i < size)
	{
		pid = wait(&wstate);
		if (pid == last_pid)
			wstate_last = wstate;
		i++;
	}
	return (WEXITSTATUS(wstate_last));
}
