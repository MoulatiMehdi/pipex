/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 20:13:57 by mmoulati          #+#    #+#             */
/*   Updated: 2025/02/06 20:14:31 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

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
