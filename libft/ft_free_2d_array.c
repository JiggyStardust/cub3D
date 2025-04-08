/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_2d_array.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sniemela <sniemela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 11:01:42 by sniemela          #+#    #+#             */
/*   Updated: 2025/04/08 11:01:52 by sniemela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_array(char ***str)
{
	size_t	i;

	if (!str || !*str)
		return ;
	i = 0;
	while ((*str)[i] != NULL)
	{
		free((*str)[i]);
		i++;
	}
	free(*str);
	*str = NULL;
}