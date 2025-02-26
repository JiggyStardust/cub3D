/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpirkola <hpirkola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 09:11:21 by hpirkola          #+#    #+#             */
/*   Updated: 2024/04/18 10:57:13 by hpirkola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	char	*charptr;
	size_t	i;

	if (count != 0 && SIZE_MAX / count < size)
		return (NULL);
	ptr = malloc(size * count);
	if (ptr == NULL)
		return (NULL);
	i = 0;
	charptr = (char *) ptr;
	while (i < (size * count))
		charptr[i++] = 0;
	return (ptr);
}
