/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpirkola <hpirkola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:53:43 by hpirkola          #+#    #+#             */
/*   Updated: 2024/07/11 17:56:11 by hpirkola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 8
# endif

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include "../libft.h"

char	*get_next_line(int fd);
int		find_line_break(char *static_buf);
char	*copy_line(char *static_buf);
char	*join(char *static_buf, char *buffer);
char	*next_line(char *static_buf);
char	*read_file(int fd, char *static_buf);
void	*free_the_buf(char *static_buf);
char	*allocate_line(char *static_buf);

#endif
