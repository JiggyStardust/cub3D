/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpirkola <hpirkola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 21:28:24 by hpirkola          #+#    #+#             */
/*   Updated: 2024/04/30 14:14:54 by hpirkola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static long	to_int(const char *str, int neg)
{
	int		i;
	long	result;

	i = 0;
	result = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if ((result > 9223372036854775807 / 10) \
			|| (result == 9223372036854775807 / 10 && str[i] - '0' > 7))
		{
			if (neg == 1)
				return (-1);
			else
				return (0);
		}
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * neg);
}

int	ft_atoi(const char *str)
{
	int	neg;
	int	result;

	neg = 1;
	result = 0;
	while (*str == ' ' || *str == '\n' || *str == '\t' || *str == '\v' \
			|| *str == '\f' || *str == '\r')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			neg *= -1;
		str++;
	}
	result = (int) to_int(str, neg);
	return (result);
}
