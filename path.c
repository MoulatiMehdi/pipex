/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 16:32:17 by mmoulati          #+#    #+#             */
/*   Updated: 2025/02/01 16:39:53 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cmd.h"

bool	ft_ispath(char *str)
{
	return (ft_strchr(str, '/'));
}

char	*ft_path_join(char *dir, char *filename)
{
	char	*dirname;
	char	*cmd;

	dirname = ft_strjoin(dir, "/");
	cmd = ft_strjoin(dirname, filename);
	free(dirname);
	return (cmd);
}

char	*ft_path_cmd(char *filename)
{
	char	**path_dirs;
	char	*cmd;
	char	*fullpath;
	int		i;

	fullpath = NULL;
	path_dirs = ft_split(ft_env_get("PATH"), ":");
	if (path_dirs == NULL)
		return (NULL);
	i = 0;
	while (path_dirs[i])
	{
		cmd = ft_path_join(path_dirs[i], filename);
		if (access(cmd, F_OK) == 0)
		{
			fullpath = cmd;
			break ;
		}
		free(cmd);
		i++;
	}
	ft_split_free(&path_dirs);
	return (fullpath);
}
