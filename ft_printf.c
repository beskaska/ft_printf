/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 21:57:51 by aimelda           #+#    #+#             */
/*   Updated: 2020/01/26 13:04:29 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		parcing(const char **format, va_list *ap)
{
	char	sign_space;
	char	zero_space;

	sign_space = NULL;
	zero_space = ' ';

	(*format)++;

	if (**format == 'd')
		ft_putnbr(va_arg(*ap, int));
	return (1);
}

int		ft_printf(const char *format, ...)
{
	va_list	ap;
	int		sum;

	va_start(ap, format);
	sum = 0;
	while (*format)
	{
		if (*format == '%')
			sum += parcing(&format, &ap); //need to handle error '-1'
		else
		{
			write(1, format, 1);
			sum++;
		}
		format++;
	}
	va_end(ap);
	return (sum);
}