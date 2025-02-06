/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 18:51:01 by mmoulati          #+#    #+#             */
/*   Updated: 2025/02/06 19:35:53 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include "config.h"
# include "libft/libft.h"
# include <errno.h>
# include <string.h>
# include <unistd.h>

void	ft_shell_error(char *str1, char *str2);
int		ft_shell_perror(char *str);

#endif
