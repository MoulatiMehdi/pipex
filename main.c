/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 17:59:16 by mmoulati          #+#    #+#             */
/*   Updated: 2025/02/03 18:26:10 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

char	*g_cmd[][4] = {
	{"/bin/cat", NULL},
	{"/bin/grep", NULL},
	{"/bin/ls", "-l", NULL},
};

int	*t_redirect_new(char *in_file, char *out_file, bool append)
{
	int	o_flag;
	int	*fds;

	fds = t_fds_new();
	if (fds == NULL)
		return (NULL);
	o_flag = O_WRONLY | O_CREAT | O_TRUNC;
	if (append)
		o_flag = O_WRONLY | O_CREAT | O_APPEND;
	if (in_file)
		fds[0] = open(in_file, O_RDONLY);
	else
		fds[0] = dup(STDIN_FILENO);
	if (out_file)
		fds[1] = open(out_file, o_flag, 0644);
	else
		fds[1] = dup(STDOUT_FILENO);
	if (fds[1] < 0 || fds[0] < 0)
	{
		t_fds_clear(&fds);
		return (NULL);
	}
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	return (fds);
}

int	main(int argc, char *argv[])
{
	int		size;
	int		*fds;
	int		**pipes;
	pid_t	last_pid;

	size = sizeof(g_cmd) / sizeof(g_cmd[0]);
	fds = t_redirect_new(NULL, NULL, false);
	fprintf(stderr, "commands : %d\n", size);
	if (fds == NULL)
	{
		perror(SHELL_NAME);
		exit(errno);
	}
	fprintf(stderr, "fd_in : %d\nfd_out : %d\n", fds[0], fds[1]);
	pipes = t_pipes_new(size - 1);
	if (pipes == NULL)
		t_fds_error(&fds);
	last_pid = t_process_childs(pipes, fds, size);
	t_fds_clear(&fds);
	t_pipes_clear(&pipes);
	if (last_pid == -1)
	{
		perror(SHELL_NAME);
		exit(errno);
	}
	return (t_process_wait(last_pid, size));
}
