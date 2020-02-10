/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specifiers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 13:39:29 by aimelda           #+#    #+#             */
/*   Updated: 2020/02/10 23:11:25 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*signed_decimal(long long n, t_printf *cur)
{
	int			len;
	long long	nb;
	char		*res;

	nb = n;
	while (nb /= 10)
		cur->arg_length++;
	if (n < 0)
		++cur->arg_length;
	res = (char*)malloc(cur->arg_length + 1);
	if (!res)
		return (NULL);
	res[0] = '-';
	res[cur->arg_length] = 0;
	len = cur->arg_length;
	while (len-- > 0)
	{
		res[len] = ft_abs(n % 10) + '0';
		n /= 10;
	}
	return (res);
}

static char	*unsigned_decimal(unsigned long long n, t_printf *cur)
{
	int					len;
	unsigned long long	nb;
	char				*res;

	nb = n;
	while (nb /= 10)
		++cur->arg_length;
	res = (char*)malloc(cur->arg_length + 1);
	if (!res)
		return (NULL);
	res[cur->arg_length] = 0;
	len = cur->arg_length;
	while (len-- > 0)
	{
		res[len] = n % 10 + '0';
		n /= 10;
	}
	return (res);
}

static char	*unsigned_octal(unsigned long long n, t_printf *cur)
{
	int					len;
	unsigned long long	nb;
	char				*res;

	nb = n;
	while (nb /= 8)
		++cur->arg_length;
	res = (char*)malloc(cur->arg_length + 1);
	if (!res)
		return (NULL);
	res[cur->arg_length] = 0;
	len = cur->arg_length;
	while (len-- > 0)
	{
		res[len] = n % 8 + '0';
		n /= 8;
	}
	return (res);
}

static char	*unsigned_hexadecimal(unsigned long long n, t_printf *cur, char c)
{
	int					len;
	unsigned long long	nb;
	char				*res;

	nb = n;
	while (nb /= 16)
		++cur->arg_length;
	res = (char*)malloc(cur->arg_length + 1);
	if (!res)
		return (NULL);
	res[cur->arg_length] = 0;
	len = cur->arg_length;
	while (len-- > 0)
	{
		res[len] = n % 16 + '0';
		if (res[len] > '9')
			res[len] = c + res[len] - 58;
		n /= 16;
	}
	return (res);
}

void	to_diouxX(t_args *arg, va_list ap)
{
	long long	d;

	if (!(arg->arg_type % 'h' % 'h'))
		d = (long long)va_arg(ap, char);
	else if (!(arg->arg_type % 'h'))
		d = (long long)va_arg(ap, short);
	else if (!(arg->arg_type % 'l' % 'l'))
		d = va_arg(ap, long long);
	else if (!(arg->arg_type % 'l'))
		d = (long long)va_arg(ap, long);
	else
		d = (long long)va_arg(ap, int);
	if (!(arg->arg_type % 'd') || !(arg->arg_type % 'i'))
		arg->usedin->arg_text = signed_decimal(d, arg->usedin);
	else if (!(arg->arg_type % 'o'))
		arg->usedin->arg_text = unsigned_octal(d, arg->usedin);
	else if (!(arg->arg_type % 'u'))
		arg->usedin->arg_text = unsigned_decimal(d, arg->usedin);
	else if (!(arg->arg_type % 'x'))
		arg->usedin->arg_text = unsigned_hexadecimal(d, arg->usedin, 'a');
	else if (!(arg->arg_type % 'X'))
		arg->usedin->arg_text = unsigned_hexadecimal(d, arg->usedin, 'A');
}
