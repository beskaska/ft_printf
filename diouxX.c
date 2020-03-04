/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diouxX.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 13:39:29 by aimelda           #+#    #+#             */
/*   Updated: 2020/03/02 22:42:29 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	get_length(t_printf *cur, int base)
{
	int					len;
	unsigned long long	n;

	n = *(unsigned long long*)cur->content;
	if (!cur->precision && !n && cur->precision_asterisk > -1)
		return (0);
	len = 1;
	while (n /= base)
		len++;
	return (len);
}

static void	get_string(t_printf *cur, int len, int base, char c)
{
	char				*res;
	unsigned long long	n;

	n = *(unsigned long long*)cur->content;
	while (cur->precision-- > len)
		ft_putchar('0');
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

int			to_signed_dec(t_printf *cur, int base)
{
	int					len;
	int					tmp;

	if (*(long long*)cur->content < 0)
		cur->sign = '-';
	*(long long*)cur->content = ft_abs(*(long long*)cur->content);
	len = get_length(cur, base);
	tmp = ft_max(len, cur->precision) + (cur->sign > 0);
	if (cur->zero == '0')
	{
		ft_putchar(cur->sign);
		printf("!\n");
	}
	if (!(cur->left_adjusted))
		while (cur->width > tmp++)
			ft_putchar(cur->zero);
	if (cur->zero == ' ')
		ft_putchar(cur->sign);
	get_string(cur, len, base, 0);
	if (cur->left_adjusted)
		while (cur->width > tmp++)
			ft_putchar(cur->zero);
	free(cur->content);
	return (tmp - 1);
}

int			to_unsigned_num(t_printf *cur, int base)
{
	int		len;
	int		tmp;

	len = get_length(cur, base);
	tmp = ft_max(len, cur->precision);
	if (base == 8)
		tmp += cur->sharp;
	if (!(cur->left_adjusted))
		while (cur->width > tmp++)
			ft_putchar(cur->zero);
	if (base == 8 && cur->sharp && cur->precision <= len)
		ft_putchar('0');
	get_string(cur, len, base, 0);
	if (cur->left_adjusted)
		while (cur->width > tmp++)
			ft_putchar(cur->zero);
	free(cur->content);
	return (tmp - 1);
}

int			to_unsigned_hex(t_printf *cur, unsigned long long n, int base)
{
	int					len;
	unsigned long long	nb;
	int					tmp;

	len = get_length(cur, base);
	tmp = ft_max(len, cur->precision) + 2 * cur->sharp * (n > 0);
	if (cur->zero == '0' && cur->sharp && n > 0)
	{
		ft_putchar('0');
		ft_putchar(cur->arg_type);
	}
	if (!(cur->left_adjusted))
		while (cur->width > tmp++)
			ft_putchar(cur->zero);
	if (cur->zero == ' ' && cur->sharp && n > 0)
	{
		ft_putchar('0');
		ft_putchar(cur->arg_type);
	}
	get_string(cur, len, base, cur->arg_type - 81);
	if (cur->left_adjusted)
		while (cur->width > tmp++)
			ft_putchar(cur->zero);
	return (tmp - 1);
}
