/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 18:51:01 by mmoulati          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/02/08 20:26:56 by mmoulati         ###   ########.fr       */
=======
/*   Updated: 2025/02/08 20:48:41 by mmoulati         ###   ########.fr       */
>>>>>>> error
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H

# define ERROR_H

# define SHELL_NAME "pipex"
# define PROMPT_HERE_DOC "> "
# define ARGS_SEPERATOR " \t"

# include "libft/libft.h"
# include <errno.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

void	ft_shell_error(char *str1, char *str2);
int		ft_shell_perror(char *str);
int		ft_shell_code(int wstate);

#endif
