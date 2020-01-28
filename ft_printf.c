/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 21:57:51 by aimelda           #+#    #+#             */
/*   Updated: 2020/01/28 21:47:07 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static t_printf	*new_node(const char *format)
{
	t_printf	*tmp;

	tmp = (t_printf*)malloc(sizeof(t_printf));
	tmp->text = format;
	tmp->text_length = 0;
	tmp->arg_number = 1; //maybe should passing as a parameter?
	//tmp->arg_type?
	tmp->sign = 0;
	tmp->zero = 0;
	tmp->sharp = 0;
	tmp->left_adjusted = 0;
	tmp->width_asterisk = 0;
	tmp->width = 0;
	tmp->precision_asterisk_or_defined = 0;
	tmp->precision = 0;
	tmp->next = NULL;
}

static int		argument_or_width(const char **str, t_printf *cur, t_args **args)
{
	size_t	res;

	res = 0;
	while (ft_isdigit(**str))
	{
		res = res * 10 + **str - '0';
		(*str)++;
	}
	if (**str == '$')
		args[res]->usedin = cur; //need to save max_arg
	else
	{
		cur->width = res;
		(*str)--;
	}
	return (res); //no need?
}

static int		parsing(const char **format, t_printf *cur, t_args **args)
{
	while ((*format)++)
		if (ft_isdigit(**format))
			argument_or_width(format, cur, args);
		else if (**format == '+' || **format == ' ')
			cur->sign = **format;
		else if (**format == '0')
			cur->zero = '0';
		else if (**format == '#')
			cur->sharp = 1;
		else if (**format == '-')
			cur->left_adjusted = 1;
		else if (**format == '.')
			;//precision
		else if (**format == '*')
			;//width
		/*else if (**format == '%')
			;//%  always true???*/
		else
			break;
	if (ft_strchr("cspdiouxXfeghlL", **format))
		;//type and size
}

static int		look_up(const char *format, va_list *ap, t_printf *cur)
{
	int			sum;
	int			max_arg;
	t_args		*args[190];

	sum = 0;
	max_arg = 0;
	while (*format)
	{
		if (*format == '%')
		{
			parsing(&format, cur, args);
		}
		else
			cur->text_length++;
		format++;
	}
}

int		ft_printf(const char *format, ...)
{
	va_list		ap;
	int			sum;
	t_printf	*head;

	va_start(ap, format);
	head = new_node(format);
	sum = look_up(format, &ap, head);
	va_end(ap);
	return (sum);
}