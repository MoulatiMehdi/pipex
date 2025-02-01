/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 20:08:28 by mmoulati          #+#    #+#             */
/*   Updated: 2025/02/01 17:45:13 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"
#include "libft/libft.h"
#include <errno.h>
#include <stdio.h>
#include <string.h>

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

void	ft_cmd_error(char *msg, char *cmd)
{
	if (msg == NULL || cmd == NULL)
		return ;
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(cmd, 2);
}

int	ft_cmd_exec(char *cmd)
{
	char	**strs;
	char	*p;

	if (cmd == NULL)
		return (0);
	strs = ft_split(cmd, " \n\t");
	if (strs == NULL)
		return (-1);
	p = strs[0];
	if (!ft_ispath(strs[0]))
	{
		p = ft_path_cmd(strs[0]);
		if (p == NULL)
		{
			ft_cmd_error("command not found", strs[0]);
			ft_split_free(&strs);
			return (-1);
		}
	}
	execve(p, strs, NULL);
	ft_cmd_error(strerror(errno), strs[0]);
	ft_split_free(&strs);
	return (0);
}

int	main(int argc, char *argv[])
{
	if (argc < 2)
		return (0);
	ft_cmd_exec(argv[1]);
	return (EXIT_SUCCESS);
}
