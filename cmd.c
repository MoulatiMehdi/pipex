/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 20:08:28 by mmoulati          #+#    #+#             */
/*   Updated: 2025/02/01 11:48:40 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

extern char	**environ;

char	*t_path_join(char *dir, char *filename)
{
	char	*dirname;
	char	*cmd;

	dirname = ft_strjoin(dir, "/");
	cmd = ft_strjoin(dirname, filename);
	free(dirname);
	return (cmd);
}

char	*t_cmd_fullpath(char *name)
{
	int		i;
	int		j;
	char	*cmd;
	char	**strs;

	i = 0;
	while (environ[i])
	{
		if (ft_strncmp(environ[i], "PATH=", 5) == 0)
		{
			strs = ft_split(&environ[i][5], ":");
			j = 0;
			while (strs[j] != NULL)
			{
				cmd = t_path_join(strs[j], name);
				if (access(cmd, F_OK | X_OK) == 0)
					return (cmd);
				free(cmd);
				j++;
			}
			break ;
		}
		i++;
	}
	return (NULL);
}

bool	ispath(char *str)
{
	int	test;

	test += ft_strncmp("/", str, 1) == 0;
	test += ft_strncmp("./", str, 2) == 0;
	test += ft_strncmp("../", str, 3) == 0;
	return (test > 0);
}

int	t_cmd_run(char *cmd, char **envp)
{
	char	**strs;
	char	*p;

	if (cmd == NULL)
		return (0);
	strs = ft_split(cmd, " \n\t");
	p = NULL;
	if ()
	{
		if (access(strs[0], F_OK | X_OK) == 0)
			p = strs[0];
	}
	else
		p = t_cmd_fullpath(strs[0]);
	execve(p, strs, envp);
	perror(p);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_cmd_run(argv[1], NULL);
	return (EXIT_SUCCESS);
}
