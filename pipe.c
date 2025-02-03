/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 19:55:29 by mmoulati          #+#    #+#             */
/*   Updated: 2025/02/03 18:55:14 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipe.h"
#include <unistd.h>

int	*t_pipe_new(void)
{
	int	*fds;

	fds = t_fds_new();
	if (fds == NULL)
		return (NULL);
	if (pipe(fds) < 0)
	{
		free(fds);
		fds = NULL;
	}
	return (fds);
}

int	**t_pipes_new(unsigned int n)
{
	int				**pipes;
	unsigned int	i;

	if (n == 0)
		return (NULL);
	i = 0;
	pipes = malloc(sizeof(int *) * (n + 1));
	if (pipes == NULL)
		return (NULL);
	while (i < n)
	{
		pipes[i] = t_pipe_new();
		if (pipes[i] == NULL)
		{
			while (i--)
				t_fds_clear(&pipes[i]);
			free(pipes);
			return (NULL);
		}
		i++;
	}
	pipes[i] = NULL;
	return (pipes);
}

void	t_pipes_close(int **pipes)
{
	unsigned int	i;

	i = 0;
	if (pipes == NULL)
		return ;
	while (pipes[i])
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

void	t_pipes_set(int **pipes, unsigned int idx)
{
	int	i;

	if (pipes == NULL || pipes[0] == NULL)
		return ;
	i = 0;
	while (pipes[i])
	{
		if (idx != i)
			close(pipes[i][1]);
		else
			dup2(pipes[i][1], STDOUT_FILENO);
		if (idx - 1 != i)
			close(pipes[i][0]);
		else
			dup2(pipes[i][0], STDIN_FILENO);
		i++;
	}
}

void	t_pipes_clear(int ***pipes)
{
	unsigned int	i;

	i = 0;
	if (pipes == NULL)
		return ;
	while ((*pipes)[i])
	{
		t_fds_clear(&(*pipes)[i]);
		i++;
	}
	free(*pipes);
	pipes = NULL;
}
/*
i = 0   0 1
i = 1   1 1 0 0
i = 2   2 1 1 0
i = 3   3 1 2 0
i = 4       3 0

*/
