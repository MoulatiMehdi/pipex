/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 11:51:30 by mmoulati          #+#    #+#             */
/*   Updated: 2025/02/08 17:52:16 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int	ft_heredoc_warn(char *delimiter)
{
	if (delimiter == NULL)
		return (0);
	ft_putstr_fd("\n" SHELL_NAME ": ", 2);
	ft_putstr_fd("warning: here-document delimited by end-of-file ", 2);
	ft_putstr_fd("(wanted `", 2);
	ft_putstr_fd(delimiter, 2);
	ft_putendl_fd("')", 2);
	return (1);
}

static int	ft_heredoc_iseof(char *eof, char *p, int n)
{
	if (eof == p)
		return (1);
	return (ft_strncmp(p, eof, n) == 0 && p[n] == '\n' && p[n + 1] == '\0');
}

static char	*ft_heredoc_getline(int fd)
{
	char	*line;
	char	*p;

	line = NULL;
	ft_putstr_fd(PROMPT_HERE_DOC, 2);
	while (1)
	{
		errno = 0;
		p = get_next_line(fd);
		if (errno == ENOMEM)
			break ;
		if (line == NULL && p == NULL)
			break ;
		if (p != NULL)
			ft_strconcat(&line, p);
		if (p != NULL && ft_strchr(p, '\n'))
			break ;
		free(p);
	}
	free(p);
	return (line);
}

char	*ft_heredoc(char *delimiter, int fd_in)
{
	char	*line;
	char	*text;
	int		size;

	if (delimiter == NULL)
		return (NULL);
	text = NULL;
	size = ft_strlen(delimiter);
	while (1)
	{
		line = ft_heredoc_getline(fd_in);
		if (delimiter && !line)
		{
			ft_heredoc_warn(delimiter);
			break ;
		}
		if (ft_heredoc_iseof(delimiter, line, size))
			break ;
		ft_strconcat(&text, line);
		free(line);
	}
	free(line);
	return (text);
}
