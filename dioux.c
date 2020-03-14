/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dioux.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 13:39:29 by aimelda           #+#    #+#             */
/*   Updated: 2020/03/09 19:42:04 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	get_length(t_printf *cur, char base, unsigned long long *nb)
{
	int					len;
	unsigned long long	n;

	n = *(unsigned long long*)cur->content;
	if (!cur->precision && !n && cur->precision_ast > -1)
		return (0);
	*nb = 1;
	len = 1;
	while (n /= base)
	{
		len++;
		*nb *= base;
	}
	return (len);
}

static void	put_string(t_printf *cur, unsigned long long nb, char base, int len)
{
	char				tmp;
	char				c;
	unsigned long long	n;

	while (cur->precision-- > len)
		ft_putchar('0');
	n = *(unsigned long long*)cur->content;
	c = base - 81;
	if (base > 10)
		base = 16;
	if (len && !n)
		ft_putchar('0');
	else if (len)
		while (nb)
		{
			tmp = n / nb + '0';
			if (tmp > '9')
				tmp += c;
			ft_putchar(tmp);
			n %= nb;
			nb /= base;
		}
	free(cur->content);
}

int			to_signed_dec(t_printf *cur, char base)
{
	int					len;
	int					tmp;
	unsigned long long	nb;

	if (*(long long*)cur->content < 0)
		cur->sign = '-';
	*(long long*)cur->content = ft_abs(*(long long*)cur->content);
	len = get_length(cur, base, &nb);
	tmp = ft_max(len, cur->precision) + (cur->sign > 0);
	if (cur->zero == '0' && cur->sign)
		ft_putchar(cur->sign);
	if (!(cur->left_adjusted))
		while (cur->width > tmp++)
			ft_putchar(cur->zero);
	if (cur->zero == ' ' && cur->sign)
		ft_putchar(cur->sign);
	put_string(cur, nb, base, len);
	if (cur->left_adjusted)
		while (cur->width > tmp++)
			ft_putchar(cur->zero);
	return (tmp - 1);
}

int			to_unsigned_num(t_printf *cur, char base)
{
	int					len;
	int					tmp;
	unsigned long long	nb;

	len = get_length(cur, base, &nb);
	tmp = ft_max(len, cur->precision);
	if (base == 8)
		tmp += cur->sharp * ((cur->precision <= len
		&& *(long long*)cur->content) || !len);
	if (!(cur->left_adjusted))
		while (cur->width > tmp++)
			ft_putchar(cur->zero);
	if (base == 8 && cur->sharp && ((cur->precision <= len
			&& *(long long*)cur->content) || !len))
		ft_putchar('0');
	put_string(cur, nb, base, len);
	if (cur->left_adjusted)
		while (cur->width > tmp++)
			ft_putchar(cur->zero);
	return (tmp - 1);
}

int			to_unsigned_hex(t_printf *cur, unsigned long long n, char base)
{
	int					len;
	unsigned long long	nb;
	int					t;

	len = get_length(cur, base, &nb);
	t = ft_max(len, cur->precision) + 2 * (cur->sharp < 0 || (cur->sharp && n));
	if (cur->zero == '0' && ((cur->sharp && n) || cur->sharp < 0))
	{
		ft_putchar('0');
		ft_putchar(cur->argt);
	}
	if (!(cur->left_adjusted))
		while (cur->width > t++)
			ft_putchar(cur->zero);
	if (cur->zero == ' ' && ((cur->sharp && n) || cur->sharp < 0))
	{
		ft_putchar('0');
		ft_putchar(cur->argt);
	}
	put_string(cur, nb, cur->argt, len);
	if (cur->left_adjusted)
		while (cur->width > t++)
			ft_putchar(cur->zero);
	return (t - 1);
}
