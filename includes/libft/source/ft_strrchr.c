/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkwamme <bkwamme@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 16:44:50 by bkwamme           #+#    #+#             */
/*   Updated: 2023/10/23 12:42:05 by bkwamme          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	last_position;
	int	i;

	last_position = -1;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			last_position = i;
		i++;
	}
	if (last_position != -1)
		return ((char *) &s[last_position]);
	else if (c == '\0')
		return ((char *)&s[i]);
	return (NULL);
}
