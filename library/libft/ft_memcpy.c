/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpirkola <hpirkola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 16:01:58 by hpirkola          #+#    #+#             */
/*   Updated: 2024/04/28 11:02:51 by hpirkola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*dst2;
	unsigned char	*src2;
	size_t			i;

	if (dst == 0 && src == 0)
		return (0);
	dst2 = (unsigned char *) dst;
	src2 = (unsigned char *) src;
	i = 0;
	while (i < n)
	{
		dst2[i] = src2[i];
		i++;
	}
	return (dst);
}
