/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkwamme <bkwamme@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 11:14:33 by bkwamme           #+#    #+#             */
/*   Updated: 2023/11/16 15:09:20 by bkwamme          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*node_swap;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		node_swap = (*lst)->next;
		ft_lstdelone((*lst), del);
		(*lst) = node_swap;
	}
	(*lst) = NULL;
}
