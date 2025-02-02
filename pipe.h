/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 19:55:43 by mmoulati          #+#    #+#             */
/*   Updated: 2025/02/02 10:48:41 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PIPE_H
# define PIPE_H

# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

int		*t_pipe_new(void);
int		**t_pipes_new(unsigned int n);
void	t_pipes_close(int **pipes);
void	t_pipes_set(int **pipes, unsigned int idx);
void	t_pipes_free(int ***pipes);

#endif
