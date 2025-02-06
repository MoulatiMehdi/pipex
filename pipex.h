/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 22:17:17 by mmoulati          #+#    #+#             */
/*   Updated: 2025/02/06 19:39:42 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PIPEX_H

# define PIPEX_H

# include "error.h"
# include "libft/libft.h"
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>

typedef enum e_mode
{
	FILE_WRITE_APPEND = 0,
	FILE_WRITE_TRUNCT = 1,
	FILE_READ = 2,
}		t_mode;

int		t_redirect_new(char *file, t_mode mode);
int		t_cmd_exec(char *cmd);

int		t_process_wait(pid_t pid_last, unsigned int n);
void	t_process_middle(char *cmd, int *fds, int read_fd);
pid_t	t_process_last(char *cmd, char *filename, int fd_in);
void	t_process_first(char *cmd, char *filename, int pipefd[2]);

#endif
