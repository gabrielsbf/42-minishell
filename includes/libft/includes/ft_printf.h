/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkwamme <bkwamme@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 14:20:14 by bkwamme           #+#    #+#             */
/*   Updated: 2023/11/28 11:08:54 by bkwamme          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

int	ft_ptradress(unsigned long long p);
int	ft_printui(unsigned int n);
int	ft_lowerhex(unsigned long long n);
int	ft_upperhex(unsigned int n);
int	ft_printstr(char *s);
int	ft_printnbr(int n);
int	ft_printchar(char c);
int	ft_vartype(char c, va_list args);
int	ft_printf(const char *str, ...);
int	ft_hexlen(unsigned long long n);

#endif
