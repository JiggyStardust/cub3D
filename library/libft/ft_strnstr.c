/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpirkola <hpirkola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 21:45:58 by hpirkola          #+#    #+#             */
/*   Updated: 2024/04/28 11:47:01 by hpirkola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	if (*needle == '\0')
		return ((char *) haystack);
	j = 0;
	while (*haystack && j < len)
	{
		i = 0;
		while (haystack[i] && haystack[i] == needle[i] && (j + i) < len)
		{
			if (needle[i + 1] == '\0')
				return ((char *) haystack);
			i++;
		}
		j++;
		haystack++;
	}
	return (NULL);
}
