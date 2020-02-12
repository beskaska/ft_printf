/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 16:30:25 by aimelda           #+#    #+#             */
/*   Updated: 2020/02/11 23:19:24 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static t_args	*free_args(t_args *to_del)
{
	t_args	*tmp;

	tmp = to_del->next;
	free(to_del);
	return (tmp);
}

static t_printf	*free_printf(t_printf *to_del)
{
	t_printf	*tmp;

	tmp = to_del->next;
	free(to_del);
	return (tmp);
}

static void		converting(t_args **args, va_list ap)
{
	int		i;
	t_args	*tmp;

	i = 0;
	while (++i <= args[0]->arg_type)
		while (args[i])
		{
			if (!(args[i]->arg_type % 'd') || !(args[i]->arg_type % 'i') ||
			!(args[i]->arg_type % 'o') || !(args[i]->arg_type % 'u') ||
			!(args[i]->arg_type % 'x') || !(args[i]->arg_type % 'X'))
				to_diouxX(args[i], ap);
			else if (!(args[i]->arg_type % 'f') || !(args[i]->arg_type % 'e')
			|| !(args[i]->arg_type % 'g'))
				;//to_feg(args[i], ap)
			else if (!(args[i]->arg_type % 's') || !(args[i]->arg_type % 'p'))
				;//to_sp(args[i], ap)
			else if (!(args[i]->arg_type % 'c'))
				;//to_c(args[i], ap)
			else if (args[i]->arg_type == 1)
				if (args[i]->usedin->precision_asterisk == i)
					args[i]->usedin->precision = va_arg(ap, int);
				else if (args[i]->usedin->width_asterisk == i)
					args[i]->usedin->width = va_arg(ap, int);
			args[i] = free_args(args[i]);
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
