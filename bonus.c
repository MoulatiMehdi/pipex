/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 22:17:17 by mmoulati          #+#    #+#             */
/*   Updated: 2025/02/05 23:16:46 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	t_cmd_exec(char *cmd)
{
	char	**str;
	int		status;

	status = 0;
	str = ft_split(cmd, ARGS_SEPERATOR);
	execve(str[0], str, NULL);
	if (errno == 2)
	{
		ft_shell_error("command not found: ", str[0]);
		status = 127;
	}
	else if (errno != 0)
	{
		ft_shell_perror(str[0]);
		status = 126;
	}
	ft_split_free(&str);
	exit(status);
}

int	t_redirect_new(char *file, t_mode mode)
{
	int	fd;
	int	o_flags;

	if (mode == FILE_WRITE_TRUNCT)
		fd = open(file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	else if (mode == FILE_WRITE_APPEND)
		fd = open(file, O_CREAT | O_APPEND | O_WRONLY, 0644);
	else if (mode == FILE_READ)
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
	int		i;

	if (argc != 5)
	{
		ft_putstr_fd("Usage : ./pipex file cmd1 cmd2 file.", 2);
		return (0);
	}
	t_process_first(argv[2], argv[1], fds);
	close(fds[1]);
	read_fd = fds[0];
	i = 3;
	while (i < argc - 2)
	{
		t_process_middle(argv[i], fds, read_fd);
		close(fds[1]);
		close(read_fd);
		read_fd = fds[0];
		i++;
	}
	pid = t_process_last(argv[argc - 2], argv[argc - 1], read_fd);
	close(read_fd);
	return (t_process_wait(pid, argc - 3));
}
