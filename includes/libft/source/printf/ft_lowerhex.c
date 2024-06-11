/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lowerhex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkwamme <bkwamme@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:36:39 by bkwamme           #+#    #+#             */
/*   Updated: 2023/11/28 11:37:16 by bkwamme          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	ft_set_hex(unsigned int n)
{
	if (n == 10)
		return ('a');
	else if (n == 11)
		return ('b');
	else if (n == 12)
		return ('c');
	else if (n == 13)
		return ('d');
	else if (n == 14)
		return ('e');
	else if (n == 15)
		return ('f');
	else
		return (((char)n) + '0');
}

int	ft_lowerhex(unsigned long long n)
{
	int		hexlen;
	int		len;
	char	*hex;

	len = ft_hexlen(n);
	hexlen = ft_hexlen(n);
	hex = (char *) malloc ((hexlen + 1) * sizeof(char));
	if (!hex)
		return (0);
	hex[hexlen] = '\0';
	while (hexlen > 0)
	{
		hex[--hexlen] = ft_set_hex(n % 16);
		n /= 16;
	}
	ft_printstr(hex);
	free(hex);
	return (len);
}
