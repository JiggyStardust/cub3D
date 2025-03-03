/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpirkola <hpirkola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 14:38:04 by hpirkola          #+#    #+#             */
/*   Updated: 2024/04/29 12:16:20 by hpirkola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	count_digits(long long n)
{
	int	count;

	count = 0;
	if (n <= 0)
	{
		count++;
		n = -n;
	}
	while (n > 0)
	{
		count++;
		n = n / 10;
	}
	return (count);
}

static char	*to_char(char *number, int i, long long num, int neg)
{
	int	len;

	len = i + 1;
	while (i >= 0 && num >= 0)
	{
		if (neg < 0 && i == 0)
		{
			number[0] = '-';
			break ;
		}
		number[i] = num % 10 + '0';
		i--;
		num = num / 10;
	}
	number[len] = '\0';
	return (number);
}

char	*ft_itoa(int n)
{
	char		*number;
	int			i;
	int			neg;
	int			len;
	long long	num;

	num = n;
	len = count_digits(num);
	i = len - 1;
	number = malloc(sizeof(char) * (len + 1));
	if (number == NULL)
		return (NULL);
	neg = 1;
	if (num < 0)
	{
		neg *= -1;
		num = -num;
	}
	to_char(number, i, num, neg);
	return (number);
}
