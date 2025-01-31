/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 13:17:07 by mmoulati          #+#    #+#             */
/*   Updated: 2025/01/31 21:57:38 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_strs(char const *s, char *c)
{
	size_t	count;
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	count = 0;
	while (s[i] && ft_strchr(c, s[i]) != NULL)
		i++;
	while (s[i])
	{
		while (s[i] && ft_strchr(c, s[i]) == NULL)
			i++;
		count++;
		while (s[i] && ft_strchr(c, s[i]) != NULL)
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

static size_t	len_tocopy(char const *s, char *charset)
{
	size_t	size;

	size = 0;
	while (s[size] && ft_strchr(charset, s[size]) == NULL)
		size++;
	return (size);
}

char	**ft_split(char const *s, char *charset)
{
	char	**strs;
	size_t	size;
	size_t	j;

	if (!s)
		return (NULL);
	strs = malloc(sizeof(char *) * (count_strs(s, charset) + 1));
	if (!strs)
		return (NULL);
	j = 0;
	while (*s)
	{
		while (*s && ft_strchr(charset, *s) != NULL)
			s++;
		if (!*s)
			break ;
		size = len_tocopy(s, charset);
		strs[j] = ft_substr(s, 0, size);
		if (!strs[j++])
			return (free_all(strs, j));
		s += size;
	}
	strs[j] = NULL;
	return (strs);
}
