/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkwamme <bkwamme@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 00:34:55 by bkwamme           #+#    #+#             */
/*   Updated: 2023/11/28 08:51:30 by bkwamme          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printstr(char *s)
{
	int	i;

	if (!s)
		return (ft_printstr("(null)"));
	i = 0;
	while (s[i] != '\0')
	{
		ft_printchar(s[i]);
		i++;
	}
	return (i);
}
