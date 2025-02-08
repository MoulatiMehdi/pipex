/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 22:18:55 by mmoulati          #+#    #+#             */
/*   Updated: 2025/02/08 14:25:02 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "pipex_bonus.h"
#include <unistd.h>

pid_t	t_process_last(char *cmd, char *filename, int fd_in, t_mode mode)
{
	pid_t	pid;
	int		fd;

	pid = fork();
	if (pid < 0)
	{
		ft_shell_perror("fork");
		exit(errno);
	}
	if (pid > 0)
		return (pid);
	if (filename)
		fd = t_redirect_new(filename, mode);
	dup2(fd_in, STDIN_FILENO);
	close(fd_in);
	ft_cmd_exec(cmd);
	return (pid);
}

void	t_process_middle(char *cmd, int *fds, int read_fd)
{
	pid_t	pid;

	if (pipe(fds) < 0)
	{
		ft_shell_perror("pipe");
		exit(errno);
	}
	pid = fork();
	if (pid < 0)
	{
		ft_shell_perror("fork");
		exit(errno);
	}
	else if (pid == 0)
	{
		dup2(read_fd, STDIN_FILENO);
		dup2(fds[1], STDOUT_FILENO);
		close(read_fd);
		close(fds[1]);
		close(fds[0]);
		ft_cmd_exec(cmd);
	}
}

int	t_process_wait(pid_t pid_last, unsigned int n)
{
	int		wstate;
	int		wstate_last;
	pid_t	pid;

	wstate_last = 0;
	while (n)
	{
		pid = wait(&wstate);
		if (pid == pid_last)
			wstate_last = wstate;
		n--;
	}
	return (ft_shell_code(wstate_last));
}

void	t_process_first(char *cmd, char *filename, int pipefd[2])
{
	pid_t	pid;
	int		fd;

	if (pipe(pipefd) < 0)
	{
		ft_shell_perror("pipe");
		exit(errno);
	}
	pid = fork();
	if (pid < 0)
	{
		ft_shell_perror("fork");
		exit(errno);
	}
	if (pid > 0)
		return ;
	if (filename)
		fd = t_redirect_new(filename, FILE_READ);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
	close(pipefd[0]);
	ft_cmd_exec(cmd);
}

void	t_process_first_heredoc(char *cmd, char *delimiter, int pipefd[2])
{
	pid_t	pid;
	int		fd;
	char	*str;

	if (pipe(pipefd) < 0)
	{
		ft_shell_perror("pipe");
		exit(errno);
	}
	pid = fork();
	if (pid < 0)
	{
		ft_shell_perror("fork");
		exit(errno);
	}
	if (pid > 0)
	{
		close(pipefd[0]);
		ft_putstr_fd(str, pipefd[1]);
		close(pipefd[1]);
		return ;
	}
	dup2(pipefd[0], STDIN_FILENO);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
	close(pipefd[0]);
	ft_cmd_exec(cmd);
}
