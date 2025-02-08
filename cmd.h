/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 20:10:36 by mmoulati          #+#    #+#             */
/*   Updated: 2025/02/06 20:07:58 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H
# define CMD_H

# include "error.h"
# include "libft/libft.h"
# include <stdbool.h>
# include <stdio.h>
# include <unistd.h>

int		ft_path_isdir(char *path);
char	*ft_path_cmd(char *filename);
char	*ft_env_get(char *key);
bool	ft_ispath(char *str);

#endif
