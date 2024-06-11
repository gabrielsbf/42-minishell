/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vartype.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkwamme <bkwamme@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 13:30:35 by bkwamme           #+#    #+#             */
/*   Updated: 2023/11/28 09:39:35 by bkwamme          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_vartype(char c, va_list args)
{
	int	i;

	i = 0;
	if (c == 'd' || c == 'i')
		i += ft_printnbr(va_arg (args, int));
	else if (c == 'X')
		i += ft_upperhex(va_arg (args, unsigned int));
	else if (c == 'x')
		i += ft_lowerhex(va_arg (args, unsigned int));
	else if (c == 'c')
		i += ft_printchar(va_arg (args, int));
	else if (c == 's')
		i += ft_printstr(va_arg (args, char *));
	else if (c == 'u')
		i += ft_printui(va_arg (args, unsigned int));
	else if (c == 'p')
		i += ft_ptradress(va_arg (args, unsigned long long));
	else if (c == '%')
		i += ft_printchar('%');
	return (i);
}
