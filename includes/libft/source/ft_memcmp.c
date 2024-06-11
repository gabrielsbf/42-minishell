/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkwamme <bkwamme@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:08:50 by bkwamme           #+#    #+#             */
/*   Updated: 2023/10/25 10:38:13 by bkwamme          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *b1, const void *b2, size_t len)
{
	size_t			i;
	unsigned char	*char_b1;
	unsigned char	*char_b2;

	if (len == 0)
		return (0);
	i = 0;
	char_b1 = (unsigned char *) b1;
	char_b2 = (unsigned char *) b2;
	while (i < len)
	{
		if (char_b1[i] != char_b2[i])
			return (char_b1[i] - char_b2[i]);
		i++;
	}
	return (0);
}
