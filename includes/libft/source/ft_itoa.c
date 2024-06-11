/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkwamme <bkwamme@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 01:06:16 by bkwamme           #+#    #+#             */
/*   Updated: 2023/11/16 11:34:58 by bkwamme          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_decimal_count(int n)
{
	int	i;

	i = 1;
	if (n == -2147483648)
		return (10);
	else if (n < 0)
		n *= -1;
	while (n > 9)
	{
		i++;
		n /= 10;
	}
	return (i);
}

static char	*ft_negative_itoa(int n)
{
	char	*itoa;
	int		decimal_count;

	decimal_count = ft_decimal_count(n);
	itoa = (char *) malloc (sizeof(char) * decimal_count + 2);
	if (!itoa)
		return (NULL);
	itoa[++decimal_count] = '\0';
	if (n == -2147483648)
	{
		itoa[--decimal_count] = '8';
		n = 214748364;
	}
	else
		n *= -1;
	while (1 < decimal_count)
	{
		itoa[--decimal_count] = (n % 10) + 48;
		n /= 10;
	}
	itoa[0] = '-';
	return (itoa);
}

char	*ft_itoa(int n)
{
	char	*itoa;
	int		decimal_count;

	if (n < 0)
		return (ft_negative_itoa(n));
	decimal_count = ft_decimal_count(n);
	itoa = (char *) malloc (sizeof(char) * decimal_count + 1);
	if (!itoa)
		return (NULL);
	itoa[decimal_count] = '\0';
	while (0 < decimal_count)
	{
		itoa[--decimal_count] = (n % 10) + 48;
		n /= 10;
	}
	return (itoa);
}
