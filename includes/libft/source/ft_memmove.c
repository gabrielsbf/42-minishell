/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkwamme <bkwamme@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 14:07:33 by bkwamme           #+#    #+#             */
/*   Updated: 2023/10/23 13:31:10 by bkwamme          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	int		i;
	char	*cdest;
	char	*csrc;

	cdest = (char *) dest;
	csrc = (char *) src;
	if (cdest == NULL && csrc == NULL)
		return (NULL);
	if (cdest >= csrc)
	{
		i = (int)n - 1;
		while (i >= 0)
		{
			cdest[i] = csrc[i];
			i--;
		}
	}
	else
		return (ft_memcpy(dest, (void *)src, n));
	return (dest);
}
