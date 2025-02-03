/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 11:07:44 by mmoulati          #+#    #+#             */
/*   Updated: 2025/02/03 18:38:22 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"
#include "pipe.h"

int	*t_fds_new(void)
{
	int	*fds;

	fds = malloc(sizeof(int) * 2);
	if (!fds)
		return (NULL);
	fds[0] = -1;
	fds[1] = -1;
	return (fds);
}

int	t_fds_close(int *fds)
{
	int	status;

	if (fds == NULL)
		return (0);
	status += close(fds[0]);
	status += close(fds[1]);
	return (status);
}

void	t_fds_clear(int **fds)
{
	if (fds == NULL || *fds == NULL)
		return ;
	t_fds_close(*fds);
	free(*fds);
	*fds = NULL;
}

int	t_fds_error(int **fds)
{
	if (fds != NULL)
		t_fds_clear(fds);
	perror(SHELL_NAME);
	exit(errno);
}
