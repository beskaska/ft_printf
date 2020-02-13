/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 21:57:51 by aimelda           #+#    #+#             */
/*   Updated: 2020/02/12 22:33:58 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static t_printf	*new_node(char *format)
{
	t_printf	*tmp;

	tmp = (t_printf*)malloc(sizeof(t_printf));
	tmp->text = format;
	tmp->text_length = 0;
	tmp->arg_number = 0; //NOT USED
	tmp->arg_text = NULL;
	tmp->arg_length = 1;
	tmp->sign = 0;
	tmp->zero = 0;
	tmp->sharp = 0;
	tmp->left_adjusted = 0;
	tmp->width_asterisk = -1;
	tmp->width = 0;
	tmp->precision_asterisk = -1;
	tmp->precision = 0;
	tmp->next = NULL;
	return (tmp);
}

static void		parsing(char *format, t_printf *cur, t_args **args)
{
	int			n;

	n = MAX_PRINTF_ARG;
	while (--n)
		args[n] = NULL;
	args[0] = (t_args*)malloc(sizeof(t_args));
	args[0]->arg_type = 0;
	while (*format)
		if (*format == '%')
		{
			ft_printf_parsing(&format, cur, args);
			if (*(++format))
				cur->next = new_node(format);
			cur = cur->next;
		}
		else
		{
			cur->text_length++;
			format++;
		}
}

int		ft_printf(const char *format, ...)
{
	va_list		ap;
	t_printf	*head;
	t_args		*args[MAX_PRINTF_ARG];
	
	va_start(ap, format);
	head = new_node((char*)format);
	parsing((char*)format, head, args);
	va_end(ap);
	return (ft_printf_print(head, args, ap));
}
