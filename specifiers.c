/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specifiers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 13:39:29 by aimelda           #+#    #+#             */
/*   Updated: 2020/02/09 14:17:47 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	to_signed_decimal(t_args *arg, va_list ap)
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
	arg->usedin->arg_text = ft_itoa(d);
}
