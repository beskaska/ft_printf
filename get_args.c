/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 20:19:47 by aimelda           #+#    #+#             */
/*   Updated: 2020/08/23 19:24:33 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		sasha2(t_printf *cur, va_list ap)
{
	if (!(cur->argt % 'l'))
	{
		*(long long*)cur->content = va_arg(ap, long);
		cur->argt /= 'l';
	}
	else if (!(cur->argt % 'h'))
	{
		*(long long*)cur->content = (short)va_arg(ap, int);
		cur->argt /= 'h';
		if (cur->argt != 'd' && cur->argt != 'i')
			*(long long*)cur->content &= 65535;
	}
	else
	{
		*(long long*)cur->content = va_arg(ap, int);
		if (cur->argt != 'd' && cur->argt != 'i')
			*(long long*)cur->content &= 4294967295;
	}
}

static int		get_long_long(t_printf *cur, va_list ap)
{
	if (!(cur->content = malloc(sizeof(long long))))
		return (-1);
	if (!(cur->argt % ('l' * 'l')))
	{
		*(long long*)cur->content = va_arg(ap, long long);
		cur->argt /= 'l' * 'l';
	}
	else if (!(cur->argt % ('h' * 'h')))
	{
		*(long long*)cur->content = (char)va_arg(ap, int);
		cur->argt /= 'h' * 'h';
		if (cur->argt != 'd' && cur->argt != 'i')
			*(long long*)cur->content &= 255;
	}
	else
		sasha2(cur, ap);
	if (cur->argt != 'c' && !cur->precision_ast)
		cur->zero = ' ';
	return (0);
}

static int		get_long_double(t_printf *cur, va_list ap)
{
	if (!(cur->content = malloc(sizeof(long double))))
		return (-1);
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
	if (cur->precision_ast == -1)
		cur->precision = 6;
	if (((char*)cur->content)[9] < 0)
		cur->sign = '-';
	return (0);
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
	if (cur->precision_ast == i)
	{
		if ((t = va_arg(ap, int)) < 0)
		{
			cur->precision = 0;
			cur->precision_ast = -1;
		}
		else if (!cur->precision)
			cur->precision = t;
		return (1);
	}
	if (cur->width_asterisk == i)
		return (1);
	return (0);
}

int				ft_printf_get_args(t_args **args, va_list ap, int i)
{
	t_printf	*tmp;

	while (++i < MAX_PRINTF_ARG)
		if (args[i])
		{
			tmp = args[i]->usedin;
			free_args(args[i]);
			if (get_precision_or_width(tmp, ap, i, 0))
				continue;
			if (!(tmp->argt % 'f') || !(tmp->argt % 'e') || !(tmp->argt % 'g'))
			{
				if (get_long_double(tmp, ap) == -1)
					return (-1);
			}
			else if (!(tmp->argt % 's'))
			{
				if (!(tmp->content = va_arg(ap, void*)))
					if (!(tmp->content = ft_strdup("(null)")))
						return (-1);
			}
			else if (get_long_long(tmp, ap) == -1)
				return (-1);
		}
	return (0);
}
