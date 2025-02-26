/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpirkola <hpirkola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 09:41:53 by hpirkola          #+#    #+#             */
/*   Updated: 2024/04/28 12:18:59 by hpirkola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	check_if_in_set(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

static int	count_size(char const *s1, char const *set)
{
	int	i;
	int	end;
	int	count;

	i = 0;
	end = ft_strlen(s1) - 1;
	count = 0;
	while (check_if_in_set(s1[i], set) == 1)
		i++;
	while (check_if_in_set(s1[end], set) == 1)
		end--;
	while (end >= i)
	{
		count++;
		i++;
	}
	return (count);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	char	*s2;

	i = 0;
	s2 = malloc(sizeof(char) * count_size(s1, set) + 1);
	if (s2 == NULL)
		return (NULL);
	while (check_if_in_set(s1[i], set) == 1)
		s1++;
	while (i < count_size(s1, set))
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}
