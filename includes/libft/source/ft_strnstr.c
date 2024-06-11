/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkwamme <bkwamme@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 14:36:59 by bkwamme           #+#    #+#             */
/*   Updated: 2023/11/16 17:39:42 by bkwamme          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big,	const char *little, size_t len)
{
	size_t	i;
	size_t	li;

	if (ft_strlen(little) == 0 || little == big)
		return ((char *) big);
	li = 0;
	i = 0;
	while (big[i] != '\0' && i < len)
	{
		if (big[i] == little[li])
			li++;
		else
		{
			li = 0;
			if (big[i] == little[li])
				i--;
		}
		if (little[li] == '\0')
			return ((char *) &big[i - (li - 1)]);
		i++;
	}
	return (NULL);
}
