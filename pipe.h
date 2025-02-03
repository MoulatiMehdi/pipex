/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 19:55:43 by mmoulati          #+#    #+#             */
/*   Updated: 2025/02/03 18:39:20 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PIPE_H
# define PIPE_H

# include "config.h"
# include <errno.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

void	t_fds_clear(int **fds);
int		t_fds_error(int **fds);
int		t_fds_close(int *fds);
int		*t_fds_new(void);

int		**t_pipes_new(unsigned int n);
void	t_pipes_close(int **pipes);
void	t_pipes_set(int **pipes, unsigned int idx);
void	t_pipes_clear(int ***pipes);

pid_t	t_process_childs(int **pipes, int *fds, unsigned int size);
int		t_process_wait(pid_t last_pid, unsigned int size);
#endif
