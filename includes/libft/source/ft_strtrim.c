/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkwamme <bkwamme@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 11:13:24 by bkwamme           #+#    #+#             */
/*   Updated: 2023/11/16 11:32:01 by bkwamme          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	back_index;
	size_t	front_index;

	if (!s1)
		return (NULL);
	front_index = 0;
	back_index = ft_strlen(s1);
	while (s1[front_index] && ft_strchr(set, s1[front_index]) != NULL)
		front_index++;
	while (back_index > 0 && ft_strchr(set, s1[back_index]) != NULL)
		back_index--;
	return (ft_substr(s1, front_index, (back_index - front_index + 1)));
}
