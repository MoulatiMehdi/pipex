/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 20:08:28 by mmoulati          #+#    #+#             */
/*   Updated: 2025/02/07 16:34:19 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"
#include "libft/libft.h"
#include <unistd.h>

int	ft_path_exec(char **strs)
{
	char	*fullpath;
	int		status;

	fullpath = ft_path_cmd(strs[0]);
	if (fullpath == NULL)
	{
		ft_shell_error(strs[0], "command not found");
		return (errno = 127);
	}
	execve(fullpath, strs, NULL);
	status = errno;
	ft_shell_error(strerror(status), strs[0]);
	free(fullpath);
	return (errno = status);
}

int	ft_cmd_exec(char *const cmd)
{
	char	**strs;
	int		status;

	strs = ft_split(cmd, ARGS_SEPERATOR);
	if (strs == NULL)
		return (-1);
	if (ft_strchr(strs[0], '/') == NULL)
		ft_path_exec(strs);
	else if (ft_path_isdir(strs[0]))
	{
		ft_shell_error(strs[0], strerror(21));
		errno = 126;
	}
	else
	{
		execve(strs[0], strs, NULL);
		ft_shell_error(strs[0], strerror(errno));
		errno = 126;
	}
	ft_split_free(&strs);
	return (errno);
}

int	main(int argc, char *argv[])
{
	if (argc < 2)
		return (0);
	return (ft_cmd_exec(argv[1]));
}
