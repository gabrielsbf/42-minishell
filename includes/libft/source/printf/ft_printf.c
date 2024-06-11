/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkwamme <bkwamme@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 14:18:55 by bkwamme           #+#    #+#             */
/*   Updated: 2023/11/28 11:38:10 by bkwamme          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		i;
	int		ft_count;

	va_start(args, str);
	ft_count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '%')
			ft_count += ft_vartype(str[++i], args);
		else
			ft_count += ft_printchar(str[i]);
		i++;
	}
	va_end (args);
	return (ft_count);
}
