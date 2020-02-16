/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diouxX.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 13:39:29 by aimelda           #+#    #+#             */
/*   Updated: 2020/02/15 23:08:38 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*signed_dec(t_printf *cur, long long n)
{
	int			len;
	long long	nb;

	nb = n;
	len = 0;
	while (nb /= 10)
		len++;
	if (n < 0)
		cur->sign = '-';
	while (len-- > 0)
	{
		res[len] = ft_abs(n % 10) + '0';
		n /= 10;
	}
	return (len);
}

static char	*unsigned_dec(unsigned long long n, t_printf *cur)
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

static char	*unsigned_oct(unsigned long long n, t_printf *cur)
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

static char	*unsigned_hex(unsigned long long n, t_printf *cur, char c)
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

void		to_diouxX(t_printf *cur)
{
	long long	d;

	if (cur->arg_type == 'd' || cur->arg_type == 'i')
		arg->usedin->arg_text = signed_dec(cur, (long long)cur->content);
	else if (!(arg->arg_type % 'o'))
		arg->usedin->arg_text = unsigned_oct(d, arg->usedin);
	else if (!(arg->arg_type % 'u'))
		arg->usedin->arg_text = unsigned_dec(d, arg->usedin);
	else if (!(arg->arg_type % 'x'))
		arg->usedin->arg_text = unsigned_hex(d, arg->usedin, 'a');
	else
		arg->usedin->arg_text = unsigned_hex(d, arg->usedin, 'A');
}
