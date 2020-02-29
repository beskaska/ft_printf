/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diouxX.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 13:39:29 by aimelda           #+#    #+#             */
/*   Updated: 2020/02/29 11:33:24 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	get_length(unsigned long long n, int base)
{
	int		len;

	len = 1;
	while (n /= base)
		len++;
	return (len);
}

static void	get_string(unsigned long long n, int len, int base, char c)
{
	char	*res;

	res = (char*)malloc(len + 1); //if NULL
	res[len] = 0;
	while (len--)
	{
		res[len] = n % base + '0';
		if (res[len] > '9')
			res[len] += c;
		n /= base;
	}
	ft_putstr(res);
	free(res);
}

int			to_signed_dec(unsigned long long n, t_printf *cur, int base)
{
	int					len;
	int					tmp;

	if ((long long)n < 0)
		cur->sign = '-';
	n = ft_abs((long long)n);
	len = get_length(n, base);
	tmp = ft_max(len, cur->precision) + cur->sign > 0;
	if (!(cur->left_adjusted))
		while (cur->width > tmp++)
			ft_putchar(cur->zero);
	ft_putchar(cur->sign);
	while (cur->precision > len++)
		ft_putchar('0');
	get_string(n, len - 1, base, 0);
	if (cur->left_adjusted)
		while (cur->width > tmp++)
			ft_putchar(cur->zero);
	free(cur->content);
	return (tmp - 1);
}

int			to_unsigned_num(unsigned long long n, t_printf *cur, int base)
{
	int		len;
	int		tmp;

	len = get_length(n, base);
	tmp = ft_max(len, cur->precision);
	if (!(cur->left_adjusted))
		while (cur->width > tmp++)
			ft_putchar(cur->zero);
	if (base == 8 && cur->sharp && n > 0 && cur->precision <= len)
		ft_putchar('0');
	while (cur->precision > len++)
		ft_putchar('0');
	get_string(n, len - 1, base, 0);
	if (cur->left_adjusted)
		while (cur->width > tmp++)
			ft_putchar(cur->zero);
	free(cur->content);
	return (tmp - 1);
}

int			to_unsigned_hex(unsigned long long n, t_printf *cur, int base)
{
	int					len;
	unsigned long long	nb;
	int					tmp;

	len = get_length(n, base);
	tmp = ft_max(len, cur->precision);
	if (!(cur->left_adjusted))
		while (cur->width > tmp++)
			ft_putchar(cur->zero);
	if (cur->sharp && n > 0)
	{
		ft_putchar('0');
		ft_putchar(cur->arg_type);
	}
	while (cur->precision > len++)
		ft_putchar('0');
	get_string(n, len - 1, base, cur->arg_type - 81);
	if (cur->left_adjusted)
		while (cur->width > tmp++)
			ft_putchar(cur->zero);
	return (tmp - 1);
}
