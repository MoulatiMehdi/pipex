/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 22:17:17 by mmoulati          #+#    #+#             */
/*   Updated: 2025/02/08 20:39:52 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PIPEX_BONUS_H

# define PIPEX_BONUS_H
# define SHELL_NAME "pipex"
# define PROMPT_HERE_DOC "> "
# define ARGS_SEPERATOR " \t"

# include "libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

typedef enum e_mode
{
	FILE_WRITE_APPEND = 0,
	FILE_WRITE_TRUNCT = 1,
	FILE_READ = 2,
}			t_mode;

extern char	**environ;

char		*ft_heredoc(char *delimiter, int fd_in);
int			ft_cmd_exec(char *const cmd);

int			t_redirect_new(char *file, t_mode mode);

int			t_process_wait(pid_t pid_last, unsigned int n);
void		t_process_middle(char *cmd, int *fds, int read_fd);
pid_t		t_process_last(char *cmd, char *filename, int fd_in, t_mode mode);
void		t_process_first(char *cmd, char *filename, int pipefd[2]);
void		t_process_first_heredoc(char *cmd, char *delimiter, int pipefd[2]);

int			ft_path_isdir(char *path);
char		*ft_path_cmd(char *filename);

char		*ft_env_get(char *key);

void		ft_shell_error(char *str1, char *str2);
int			ft_shell_perror(char *str);
int			ft_shell_code(int wstate);
#endif
