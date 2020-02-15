/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 16:30:25 by aimelda           #+#    #+#             */
/*   Updated: 2020/02/15 14:10:08 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	*free_args(t_args *to_del)
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

static t_printf	*free_printf(t_printf *to_del)
{
	t_printf	*tmp;

	tmp = to_del->next;
	free(to_del);
	return (tmp);
}

static void		get_long_long(t_printf *cur, va_list ap)
{
	cur->content = malloc(sizeof(long long));
	if (!(cur->arg_type % 'h' % 'h'))
	{
		cur->content = (long long)va_arg(ap, char);
		cur->arg_type /= 'h' / 'h';
	}
	else if (!(cur->arg_type % 'h'))
	{
		cur->content = (long long)va_arg(ap, short);
		cur->arg_type /= 'h';
	}
	else if (!(cur->arg_type % 'l' % 'l'))
	{
		cur->content = va_arg(ap, long long);
		cur->arg_type /= 'l' / 'l';
	}
	else if (!(cur->arg_type % 'l'))
	{
		cur->content = (long long)va_arg(ap, long);
		cur->arg_type /= 'l';
	}
	else
		cur->content = (long long)va_arg(ap, int);
}

static void		converting(t_args **args, va_list ap)
{
	int			i;
	t_printf	*tmp;

	i = 0;
	while (++i < MAX_PRINTF_ARG) //check
		if (args[i])
		{
			tmp = args[i]->usedin;
			if (!(tmp->arg_type % 'd') || !(tmp->arg_type % 'i') ||
			!(tmp->arg_type % 'o') || !(tmp->arg_type % 'u') ||
			!(tmp->arg_type % 'x') || !(tmp->arg_type % 'X') ||
			!(tmp->arg_type % 'c'))
				get_long_long(tmp, ap);
			else if (!(args[i]->arg_type % 'f') || !(args[i]->arg_type % 'e')
			|| !(args[i]->arg_type % 'g'))
				;//to_feg(args[i], ap)
			else if (!(args[i]->arg_type % 'c')) //sep func
				tmp->arg_text = (char*)ft_memset(ft_memalloc(2), va_arg(ap, int), 1);
			else if (!(args[i]->arg_type % 's'))
				tmp->arg_text = va_arg(ap, char*);
			else if (!(args[i]->arg_type % 'p'))
				;//to_p(args[i], ap)
			if (args[i]->arg_type == 1)
			{//separate function
				if (tmp->precision_asterisk == i)
					tmp->precision = va_arg(ap, int);
				if (tmp->width_asterisk == i)
					tmp->width = va_arg(ap, int);
			}
			free_args(args[i]);
		}
}

int				ft_printf_print(t_printf *cur, t_args **args, va_list ap)
{
	int		sum;

	sum = 0;
	converting(args, ap);
	while (cur)
	{
		sum += cur->text_length;
		while (cur->text_length--)
			ft_putchar(*cur->text++);
		if (cur->arg_text)
		{
			ft_putstr(cur->arg_text);
			sum += cur->arg_length;
			free(cur->arg_text);
		}
		cur = free_printf(cur);
	}
	return (sum);
}
