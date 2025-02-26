/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpirkola <hpirkola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 13:04:49 by hpirkola          #+#    #+#             */
/*   Updated: 2024/04/29 11:25:58 by hpirkola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static char	to_char(int n, int fd)
{
	char	r;

	r = n % 10 + '0';
	if (n < 10)
		return (write(fd, &r, 1));
	else
		return (to_char(n / 10, fd) + write(fd, &r, 1));
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		n = -n;
		write(fd, "-", 1);
	}
	to_char(n, fd);
}
