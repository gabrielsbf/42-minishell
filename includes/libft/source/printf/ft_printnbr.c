/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkwamme <bkwamme@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 00:44:32 by bkwamme           #+#    #+#             */
/*   Updated: 2023/11/28 11:38:39 by bkwamme          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printnbr(int n)
{
	long	num;
	int		len;

	len = 0;
	num = n;
	if (num < 0)
	{
		len += ft_printchar('-');
		num *= -1;
	}
	if (num > 9)
		len += ft_printnbr(num / 10);
	len += ft_printchar((num % 10) + '0');
	return (len);
}
