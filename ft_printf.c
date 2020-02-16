/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 21:57:51 by aimelda           #+#    #+#             */
/*   Updated: 2020/02/15 22:36:09 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static t_printf	*new_node(char *format)
{
	t_printf	*tmp;

	tmp = (t_printf*)malloc(sizeof(t_printf));
	tmp->text = format;
	tmp->text_length = 0;
	//tmp->arg_number = 0; //NOT USED
	tmp->arg_type = 1;
	tmp->arg_text = NULL; //?
	tmp->content = NULL;
	tmp->arg_length = 1;
	tmp->sign = 0;
	tmp->zero = ' ';
	tmp->sharp = 0;
	tmp->left_adjusted = 0;
	tmp->width_asterisk = -1;
	tmp->width = 0;
	tmp->precision_asterisk = -1;
	tmp->precision = 0;
	tmp->next = NULL;
	return (tmp);
}

static void		look_up(char *format, t_printf *cur, t_args **args)
{
	int			max_arg;

	max_arg = MAX_PRINTF_ARG;
	while (--max_arg)
		args[max_arg] = NULL;
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
	
	head = new_node((char*)format);
	look_up((char*)format, head, args);
	va_start(ap, format);
	ft_printf_get_args(args, ap);
	va_end(ap);
	return (ft_printf_print(head));
}
