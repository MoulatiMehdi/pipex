/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 13:17:07 by mmoulati          #+#    #+#             */
/*   Updated: 2024/11/13 21:04:03 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_strs(char const *s, char c)
{
	size_t	count;
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	count = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		while (s[i] && s[i] != c)
			i++;
		count++;
		while (s[i] && s[i] == c)
			i++;
		if (!s[i])
			break ;
	}
	return (count);
}

static char	**free_all(char **strs, size_t size)
{
	while (size--)
	{
		if (strs[size])
			free(strs[size]);
		strs[size] = NULL;
	}
	free(strs);
	strs = NULL;
	return (NULL);
}

static size_t	len_tocopy(char const *s, char c)
{
	size_t	size;

	size = 0;
	while (s[size] && s[size] != c)
		size++;
	return (size);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;
	size_t	size;
	size_t	j;

	if (!s)
		return (NULL);
	strs = malloc(sizeof(char *) * (count_strs(s, c) + 1));
	if (!strs)
		return (NULL);
	j = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (!*s)
			break ;
		size = len_tocopy(s, c);
		strs[j] = ft_substr(s, 0, size);
		if (!strs[j++])
			return (free_all(strs, j));
		s += size;
	}
	strs[j] = NULL;
	return (strs);
}
