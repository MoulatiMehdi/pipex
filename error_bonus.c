/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:14:09 by mmoulati          #+#    #+#             */
/*   Updated: 2025/02/08 11:55:20 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
	ft_shell_error(strerror(status), str);
	return (errno);
}

int	ft_shell_code(int wstate)
{
	int	code;

	code = 0;
	if ((wstate & 0x7f) == 0)
		code = ((wstate & 0xff00) >> 8);
	else if (((signed char)((wstate & 0x7f) + 1) >> 1) > 0)
		code = ((wstate & 0x7f) + 128);
	else if ((wstate & 0xff) == 0x7f)
		code = (((wstate & 0xff00) >> 8) + 128);
	return (code);
}
