/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpirkola <hpirkola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 16:09:15 by hpirkola          #+#    #+#             */
/*   Updated: 2024/04/28 12:04:34 by hpirkola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*str;
	unsigned int	i;
	size_t			sub_len;

	sub_len = 0;
	if (start <= ft_strlen(s))
	{
		sub_len = ft_strlen(s + start);
		if (sub_len > len)
			sub_len = len;
	}
	str = malloc(sizeof(char) * sub_len + 1);
	if (str == NULL)
		return (NULL);
	i = 0;
	while (i < sub_len)
	{
		str[i] = s[start];
		i++;
		start++;
	}
	str[i] = '\0';
	return (str);
}
