/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 22:17:17 by mmoulati          #+#    #+#             */
/*   Updated: 2025/02/09 13:46:05 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PIPEX_H

# define PIPEX_H
# define SHELL_NAME "pipex"
# define PROMPT_HERE_DOC "> "
# define ARGS_SEPERATOR " \t"

# include "libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

extern char	**environ;

typedef enum e_mode
{
	FILE_WRITE_APPEND = 0,
	FILE_WRITE_TRUNCT = 1,
	FILE_READ = 2,
}			t_mode;

int			t_redirect_new(char *file, t_mode mode);
int			ft_cmd_exec(char *cmd);

int			t_process_wait(pid_t pid_last, unsigned int n);
void		t_process_middle(char *cmd, int *fds, int read_fd);
pid_t		t_process_last(char *cmd, char *filename, int fd_in, t_mode mode);
void		t_process_first(char *cmd, char *filename, int pipefd[2]);

int			ft_path_isdir(char *path);
char		*ft_path_cmd(char *filename);
char		*ft_env_get(char *key);

void		ft_shell_error(char *str1, char *str2);
int			ft_shell_perror(char *str);
int			ft_shell_code(int wstate);

void		ft_shell_error(char *str1, char *str2);
int			ft_shell_perror(char *str);
int			ft_shell_code(int wstate);
#endif
