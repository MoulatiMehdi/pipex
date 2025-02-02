/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 20:10:36 by mmoulati          #+#    #+#             */
/*   Updated: 2025/02/02 20:27:17 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H
# define CMD_H

# include "config.h"
# include "libft/libft.h"
# include <errno.h>
# include <stdbool.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>

int		ft_path_isdir(char *path);
char	*ft_path_cmd(char *filename);
char	*ft_env_get(char *key);
bool	ft_ispath(char *str);

#endif
