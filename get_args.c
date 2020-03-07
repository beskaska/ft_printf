/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 20:19:47 by aimelda           #+#    #+#             */
/*   Updated: 2020/03/07 15:48:54 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	free_args(t_args *to_del)
{
	t_args	*tmp;

	while (to_del->next)
	{
		tmp = to_del->next;
		tmp->usedin->content = to_del->usedin->content;
		free(to_del);
		to_del = tmp;
	}
	free(to_del);
}

static void		get_long_long(t_printf *cur, va_list ap)
{
	cur->content = malloc(sizeof(long long));//if NULL
	if (!(cur->arg_type % ('l' * 'l')))
	{
		*(long long*)cur->content = va_arg(ap, long long);
		cur->arg_type /= 'l' * 'l';
	}
	else if (!(cur->arg_type % ('h' * 'h')))
	{
		*(long long*)cur->content = va_arg(ap, char);
		cur->arg_type /=  'h' * 'h';
		if (cur->arg_type != 'd' && cur->arg_type != 'i')
			*(long long*)cur->content &= 255;//!
	}
	else if (!(cur->arg_type % 'l'))
	{
		*(long long*)cur->content = va_arg(ap, long);
		cur->arg_type /= 'l';
	}
	else if (!(cur->arg_type % 'h'))
	{
		*(long long*)cur->content = (int)va_arg(ap, short);
		cur->arg_type /= 'h';
		if (cur->arg_type != 'd' && cur->arg_type != 'i')
			*(long long*)cur->content &= 65535;//!
	}
	else
	{
		*(long long*)cur->content = va_arg(ap, int);
		if (cur->arg_type != 'd' && cur->arg_type != 'i')
			*(long long*)cur->content &= 4294967295;//!
	}
	if (cur->arg_type != 'c' && !cur->precision_asterisk)
		cur->zero = ' ';
}

static void		get_long_double(t_printf *cur, va_list ap)
{
	cur->content = malloc(sizeof(long double));//if NULL
	if (!(cur->arg_type % 'l'))
	{
		*(long double*)cur->content = va_arg(ap, double);
		cur->arg_type /= 'l';
	}
	else if (!(cur->arg_type % 'L'))
	{
		*(long double*)cur->content = va_arg(ap, long double);
		cur->arg_type /= 'L';
	}
	else
		*(long double*)cur->content = va_arg(ap, double);
	if (cur->precision_asterisk == -1)
		cur->precision = 6;
}

static int		get_precision_or_width(t_printf *cur, va_list ap, int i)
{
	int		tmp;

	if (cur->width_asterisk == i)
	{
		if ((tmp = va_arg(ap, int)) < 0)
		{
			cur->left_adjusted = 1;
			cur->zero = ' ';
			cur->width = ft_abs(tmp);
		}
		else if (!cur->width)
			cur->width = tmp;
		return (1);
	}
	if (cur->precision_asterisk == i)
	{
		if ((tmp = va_arg(ap, int)) < 0)
		{
			cur->precision = 0;
			cur->precision_asterisk = -1;
		}
		else if (!cur->precision)
			cur->precision = tmp;
		return (1);
	}
	return (0);
}

void			ft_printf_get_args(t_args **args, va_list ap)
{
	int			i;
	t_printf	*tmp;

	i = 0;
	while (++i < MAX_PRINTF_ARG) //check the restriction | max_arg
		if (args[i])
		{
			tmp = args[i]->usedin;
			if (get_precision_or_width(tmp, ap, i))
				continue;
			if (tmp->arg_type == 'p')
			{
				tmp->arg_type = 'l' * 'l' * 'x';
				tmp->sharp = -1;
			}
			if (!(tmp->arg_type % 'd') || !(tmp->arg_type % 'i') ||
			!(tmp->arg_type % 'o') || !(tmp->arg_type % 'u') ||
			!(tmp->arg_type % 'x') || !(tmp->arg_type % 'X') ||
			!(tmp->arg_type % 'c'))
				get_long_long(tmp, ap);
			else if (!(tmp->arg_type % 'f') || !(tmp->arg_type % 'e')
			|| !(tmp->arg_type % 'g'))
				get_long_double(tmp, ap);
			else if (!(tmp->arg_type % 's'))
				if (!(tmp->content = va_arg(ap, void*)))
					tmp->content = ft_strdup("(null)");
			free_args(args[i]);
		}
}
