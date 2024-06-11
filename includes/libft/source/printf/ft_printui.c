/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printui.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkwamme <bkwamme@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 13:43:47 by bkwamme           #+#    #+#             */
/*   Updated: 2023/11/28 11:02:17 by bkwamme          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printui(unsigned int n)
{
	int	len;

	len = 0;
	if (n > 9)
		len += ft_printui(n / 10);
	len += ft_printchar((n % 10) + '0');
	return (len);
}
