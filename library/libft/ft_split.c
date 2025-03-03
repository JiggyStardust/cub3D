/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpirkola <hpirkola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 13:16:48 by hpirkola          #+#    #+#             */
/*   Updated: 2024/06/13 14:31:18 by hpirkola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static char	*ft_strndup(char const *s, int len, int i)
{
	char	*dest;
	int		j;

	j = 0;
	dest = malloc(sizeof(char) * (len + 1));
	if (dest == NULL)
		return (NULL);
	while (j < len && s[i] != '\0')
	{
		dest[j] = s[i];
		i++;
		j++;
	}
	dest[j] = '\0';
	return (dest);
}

static int	ft_words(char const *s, char c, int flag, int count)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			if (flag == 1)
			{
				count++;
				flag = 0;
			}
		}
		else
			flag = 1;
		i++;
	}
	return (count);
}

static int	ft_word_length(char const *s, char c, int i)
{
	int	len;

	len = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			i++;
			len++;
		}
		else
			return (len);
	}
	return (len);
}

static void	*free_ptr(char **arr, int j)
{
	if (arr[j] == NULL)
	{
		while (j >= 0)
		{
			free(arr[j]);
			j--;
		}
		free(arr);
		return (NULL);
	}
	return (arr[j]);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	arr = malloc(sizeof(char *) * (ft_words(s, c, 1, 0) + 1));
	if (arr == NULL)
		return (NULL);
	while (s[i] != '\0' && j < ft_words(s, c, 1, 0))
	{
		if (s[i] != c)
		{
			arr[j++] = ft_strndup(s, ft_word_length(s, c, i), i);
			if (free_ptr(arr, j - 1) == NULL)
				return (NULL);
			i += ft_word_length(s, c, i);
		}
		else
			i++;
	}
	arr[j] = NULL;
	return (arr);
}
