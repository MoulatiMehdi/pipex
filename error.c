/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:14:09 by mmoulati          #+#    #+#             */
/*   Updated: 2025/02/10 11:49:10 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_shell_error(char *str1, char *str2)
{
	ft_putstr_fd(SHELL_NAME ": ", 2);
	if (str1)
	{
		ft_putstr_fd(str1, 2);
	}
	if (str2)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(str2, 2);
	}
	write(2, "\n", 1);
}

int	ft_shell_perror(char *str)
{
	int	status;

	status = errno;
	if (status == 0 || str == NULL)
		return (errno);
	ft_shell_error(str, strerror(status));
	return (errno);
}

int	ft_shell_code(int wstate)
{
	int	code;

	code = 0;
	if (WIFEXITED(wstate))
		code = WEXITSTATUS(wstate);
	else if (WIFSIGNALED(wstate))
		code = (WTERMSIG(wstate) + 128);
	else if (WIFSTOPPED(wstate))
		code = (WSTOPSIG(wstate) + 128);
	return (code);
}
