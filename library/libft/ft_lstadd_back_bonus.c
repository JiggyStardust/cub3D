/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpirkola <hpirkola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 12:33:53 by hpirkola          #+#    #+#             */
/*   Updated: 2024/04/29 13:06:56 by hpirkola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;

	temp = *lst;
	if (!lst)
		return ;
	if (*lst)
	{
		while ((*lst)->next != NULL)
			*lst = (*lst)->next;
		(*lst)->next = new;
		*lst = temp;
	}
	else
		*lst = new;
}
