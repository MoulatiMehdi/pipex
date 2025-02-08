/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 22:17:17 by mmoulati          #+#    #+#             */
/*   Updated: 2025/02/08 14:15:59 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "pipex_bonus.h"

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

void	t_args_check(int argc, char **argv)
{
	if (argc < 5)
	{
		ft_putstr_fd("Usage : ./pipex file cmd1 ... cmd2 file.", 2);
		exit(1);
	}
	if (argc < 6 && ft_strncmp("here_doc", argv[1], 8))
	{
		ft_putstr_fd("Usage : ./pipex here_doc DELIMITER cmd1 ... cmd2 file.",
			2);
		exit(1);
	}
}

int	main(int argc, char *argv[])
{
	int		fds[2];
	int		read_fd;
	pid_t	pid;
	int		i;
	t_mode	mode;
	char	*str;

	t_args_check(argc, argv);
	mode = FILE_WRITE_TRUNCT;
	i = 3;
	if (ft_strncmp("here_doc", argv[1], 8) == 0)
	{
		str = ft_heredoc(argv[2], STDIN_FILENO);
		if (pipe(fds) < 0)
		{
			ft_shell_perror("pipe");
			exit(errno);
		}
		ft_putstr_fd(str, fds[1]);
		mode = FILE_WRITE_APPEND;
		i = 3;
	}
	else
		t_process_first(argv[2], argv[1], fds);
	close(fds[1]);
	read_fd = fds[0];
	while (i < argc - 2)
	{
		t_process_middle(argv[i], fds, read_fd);
		close(fds[1]);
		close(read_fd);
		read_fd = fds[0];
		i++;
	}
	pid = t_process_last(argv[argc - 2], argv[argc - 1], read_fd, mode);
	close(read_fd);
	return (t_process_wait(pid, argc - 3));
}
