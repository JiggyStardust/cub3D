/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpirkola <hpirkola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 10:52:35 by hpirkola          #+#    #+#             */
/*   Updated: 2024/08/09 12:25:08 by hpirkola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*join(char *static_buf, char *buffer)
{
	char	*new_buf;

	new_buf = ft_strjoin(static_buf, buffer);
	free(static_buf);
	if (!new_buf)
		return (NULL);
	if (new_buf[0] == '\0')
	{
		free(new_buf);
		return (NULL);
	}
	return (new_buf);
}

void	*free_the_buf(char *static_buf)
{
	free(static_buf);
	return (NULL);
}

char	*allocate_line(char *static_buf)
{
	int		i;
	char	*line;

	i = 0;
	while (static_buf[i] && static_buf[i] != '\n')
		i++;
	if (static_buf[i] != '\n')
		line = malloc((i + 1) * sizeof(char));
	else
		line = malloc((i + 2) * sizeof(char));
	return (line);
}
