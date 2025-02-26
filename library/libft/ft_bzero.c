/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpirkola <hpirkola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 10:42:48 by hpirkola          #+#    #+#             */
/*   Updated: 2024/04/29 11:50:34 by hpirkola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_bzero(void *s, size_t n)
{
	unsigned char	*d;
	size_t			i;

	d = (unsigned char *) s;
	i = 0;
	while (i < n)
	{
		d[i] = 0;
		i++;
	}
	return (s);
}
