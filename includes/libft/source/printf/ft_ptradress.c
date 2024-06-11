/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptradress.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkwamme <bkwamme@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 14:27:27 by bkwamme           #+#    #+#             */
/*   Updated: 2023/11/28 09:25:23 by bkwamme          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_ptradress(unsigned long long p)
{
	if (!p)
		return (ft_printstr("(nil)"));
	return (ft_printstr("0x") + ft_lowerhex((unsigned long long) p));
}
