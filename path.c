/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 16:32:17 by mmoulati          #+#    #+#             */
/*   Updated: 2025/02/08 20:15:57 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_path_join(char *dir, char *filename)
{
	char	*fullpath;

	fullpath = ft_strjoin(dir, "/");
	ft_strconcat(&fullpath, filename);
	return (fullpath);
}

int	ft_path_isdir(char *path)
{
	char	*test_path;
	int		ans;

	if (path == 0 || path[0] == '\0')
		return (1);
	test_path = ft_strjoin(path, "/");
	if (!test_path)
		return (0);
	errno = 0;
	ans = access(test_path, F_OK);
	free(test_path);
	return (ans == 0);
}

char	*ft_path_cmd(char *filename)
{
	char	*cmd;
	char	*fullpath;
	char	**path_dirs;
	int		i;

	if (filename == NULL | filename[0] == '\0')
		return (NULL);
	fullpath = NULL;
	path_dirs = ft_split(ft_env_get("PATH"), ":");
	if (path_dirs == NULL)
		return (NULL);
	i = 0;
	while (path_dirs[i])
	{
		cmd = ft_path_join(path_dirs[i], filename);
		if (!ft_path_isdir(cmd) && access(cmd, F_OK) == 0)
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
