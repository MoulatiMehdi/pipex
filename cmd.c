/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 20:08:28 by mmoulati          #+#    #+#             */
/*   Updated: 2025/02/02 22:12:35 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"
#include "config.h"
#include "libft/libft.h"
#include <string.h>
#include <unistd.h>

extern char	**environ;

char	*ft_env_get(char *key)
{
	int	i;
	int	size;

	if (environ == NULL || key == NULL)
		return (NULL);
	i = 0;
	size = ft_strlen(key);
	while (environ[i])
	{
		if (ft_strncmp(environ[i], key, size) == 0 && environ[i][size] == '=')
			return (&environ[i][size + 1]);
		i++;
	}
	return (NULL);
}

void	ft_cmd_error(char *msg, char *cmd, char ***strs)
{
	ft_putstr_fd(SHELL_NAME ": ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(cmd, 2);
	if (cmd == NULL)
		write(1, "\n", 1);
	ft_split_free(strs);
}

int	ft_cmd_exec(char *const cmd)
{
	char	**strs;
	char	*p;

	strs = ft_split(cmd, " \n\t");
	if (strs == NULL || cmd == NULL)
		return (-1);
	p = strs[0];
	if (!ft_ispath(p))
	{
		p = ft_path_cmd(p);
		if (p == NULL)
		{
			ft_cmd_error("command not found", strs[0], &strs);
			return (127);
		}
	}
	else if (ft_path_isdir(p))
	{
		ft_cmd_error(p, strerror(21), &strs);
		return (21);
	}
	execve(p, strs, NULL);
	ft_cmd_error(strerror(errno), strs[0], &strs);
	return (errno);
}

int	main(int argc, char *argv[])
{
	if (argc < 2)
		return (0);
	return (ft_cmd_exec(argv[1]));
}
