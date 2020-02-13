/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   feg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 21:34:49 by aimelda           #+#    #+#             */
/*   Updated: 2020/02/13 21:54:02 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		to_feg(t_args *arg, va_list ap)
{
	long double	tmp;

	if (!(arg->arg_type % 'L'))
		tmp = va_arg(ap, long double);
	else
		tmp = (long double)va_arg(ap, double);
	if (!(arg->arg_type % 'f'))
		;//
	else if (!(arg->arg_type % 'e'))
		;//
	else
		;//
}
