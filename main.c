/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 22:17:17 by mmoulati          #+#    #+#             */
/*   Updated: 2025/02/08 21:34:19 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	t_redirect_new(char *file, t_mode mode)
{
	int	fd;

	fd = -1;
	if (mode == FILE_WRITE_TRUNCT)
		fd = open(file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	else if (mode == FILE_WRITE_APPEND)
		fd = open(file, O_CREAT | O_APPEND | O_WRONLY, 0644);
	else
		fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		ft_shell_perror(file);
		exit(1);
	}
	if (mode == FILE_READ)
		dup2(fd, STDIN_FILENO);
	else
		dup2(fd, STDOUT_FILENO);
	close(fd);
	return (fd);
}

int	main(int argc, char *argv[])
{
	int		fds[2];
	int		read_fd;
	pid_t	pid;

	if (argc != 5)
	{
		ft_putendl_fd("Usage : ./pipex file cmd1 cmd2 file", 2);
		return (1);
	}
	t_process_first(argv[2], argv[1], fds);
	close(fds[1]);
	read_fd = fds[0];
	pid = t_process_last(argv[argc - 2], argv[argc - 1], read_fd,
			FILE_WRITE_TRUNCT);
	close(read_fd);
	return (t_process_wait(pid, argc - 3));
}
