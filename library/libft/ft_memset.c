/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpirkola <hpirkola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 10:37:36 by hpirkola          #+#    #+#             */
/*   Updated: 2024/04/29 09:58:44 by hpirkola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*d;
	size_t			i;

	d = (unsigned char *) b;
	i = 0;
	while (i < len)
	{
		d[i] = (unsigned char) c;
		i++;
	}
	return (b);
}
