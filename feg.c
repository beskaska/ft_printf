/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   feg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 21:34:49 by aimelda           #+#    #+#             */
/*   Updated: 2020/02/18 21:29:44 by aimelda          ###   ########.fr       */
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

int			to_f(t_printf *cur, long double n)
{
	int					len;
	int					tmp;

	if ((char)cur->content < 0)
		cur->sign = '-';
	n = n << 1;
	len = get_length(nb);
	tmp = ft_max(len, cur->precision) + cur->sign > 0;
	if (!(cur->left_adjusted))
		while (cur->width > tmp++)
			ft_putchar(cur->zero);
	ft_putchar(cur->sign);
	while (cur->precision > len++)
		ft_putchar('0');
	get_string(nb, len - 1, 0);
	if (cur->left_adjusted)
		while (cur->width > tmp++)
			ft_putchar(cur->zero);
	free(cur->content);
	return (tmp - 1);
}

int			to_feg(t_printf *cur)
{
	long double	tmp;

	if (!(cur->arg_type % 'f'))
		;//
	else if (!(cur->arg_type % 'e'))
		;//
	else
		;//
}
