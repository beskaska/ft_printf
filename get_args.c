/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 20:19:47 by aimelda           #+#    #+#             */
/*   Updated: 2020/03/07 22:44:38 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		sasha2(t_printf *cur, va_list ap)
{
	if (!(cur->argt % 'h'))
	{
		*(long long*)cur->content = (int)va_arg(ap, short);
		cur->argt /= 'h';
		if (cur->argt != 'd' && cur->argt != 'i')
			*(long long*)cur->content &= 65535;//define
	}
	else
	{
		*(long long*)cur->content = va_arg(ap, int);
		if (cur->argt != 'd' && cur->argt != 'i')
			*(long long*)cur->content &= 4294967295;//define
	}
}

static void		get_long_long(t_printf *cur, va_list ap)
{
	cur->content = malloc(sizeof(long long));//if NULL
	if (!(cur->argt % ('l' * 'l')))
	{
		*(long long*)cur->content = va_arg(ap, long long);
		cur->argt /= 'l' * 'l';
	}
	else if (!(cur->argt % ('h' * 'h')))
	{
		*(long long*)cur->content = va_arg(ap, char);
		cur->argt /= 'h' * 'h';
		if (cur->argt != 'd' && cur->argt != 'i')
			*(long long*)cur->content &= 255;//define
	}
	else if (!(cur->argt % 'l'))
	{
		*(long long*)cur->content = va_arg(ap, long);
		cur->argt /= 'l';
	}
	else
		sasha2(cur, ap);
	if (cur->argt != 'c' && !cur->precision_asterisk)
		cur->zero = ' ';
}

static void		get_long_double(t_printf *cur, va_list ap)
{
	cur->content = malloc(sizeof(long double));//if NULL
	if (!(cur->argt % 'l'))
	{
		*(long double*)cur->content = va_arg(ap, double);
		cur->argt /= 'l';
	}
	else if (!(cur->argt % 'L'))
	{
		*(long double*)cur->content = va_arg(ap, long double);
		cur->argt /= 'L';
	}
	else
		*(long double*)cur->content = va_arg(ap, double);
	if (cur->precision_asterisk == -1)
		cur->precision = 6;
	if (((char*)cur->content)[9] < 0)
		cur->sign = '-';
}

static int		get_precision_or_width(t_printf *cur, va_list ap, int i, int t)
{
	if (cur->width_asterisk == i)
	{
		if ((t = va_arg(ap, int)) < 0)
		{
			cur->left_adjusted = 1;
			cur->zero = ' ';
			cur->width = ft_abs(t);
		}
		else if (!cur->width)
			cur->width = t;
	}
	if (cur->precision_asterisk == i)
	{
		if ((t = va_arg(ap, int)) < 0)
		{
			cur->precision = 0;
			cur->precision_asterisk = -1;
		}
		else if (!cur->precision)
			cur->precision = t;
		return (1);
	}
	if (cur->width_asterisk == i)
		return (1);
	return (0);
}

void			ft_printf_get_args(t_args **args, va_list ap, int i)
{
	t_printf	*tmp;

	while (++i < MAX_PRINTF_ARG)
		if (args[i])
		{
			tmp = args[i]->usedin;
			if (get_precision_or_width(tmp, ap, i, 0))
				continue;
			if (tmp->argt == 'p')
			{
				tmp->argt = 'l' * 'l' * 'x';
				tmp->sharp = -1;
			}
			if (!(tmp->argt % 'd') || !(tmp->argt % 'i') || !(tmp->argt % 'o')
			|| !(tmp->argt % 'u') || !(tmp->argt % 'x') || !(tmp->argt % 'X')
			|| !(tmp->argt % 'c'))
				get_long_long(tmp, ap);
			else if (!(tmp->argt % 'f') || !(tmp->argt % 'e')
			|| !(tmp->argt % 'g'))
				get_long_double(tmp, ap);
			else if (!(tmp->argt % 's'))
				if (!(tmp->content = va_arg(ap, void*)))
					tmp->content = ft_strdup("(null)");
			free_args(args[i]);
		}
}
