/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 21:57:51 by aimelda           #+#    #+#             */
/*   Updated: 2020/03/09 19:36:45 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		free_printf(t_printf *head)
{
	t_printf	*cur;

	while (head)
	{
		cur = head;
		head = head->next;
		free(cur->content);
		free(cur);
	}
}

static t_printf	*new_node(char *format)
{
	t_printf	*tmp;

	tmp = (t_printf*)malloc(sizeof(t_printf));
	tmp->text = format;
	tmp->text_length = 0;
	tmp->argt = 1;
	tmp->content = NULL;
	tmp->sign = 0;
	tmp->zero = ' ';
	tmp->sharp = 0;
	tmp->left_adjusted = 0;
	tmp->error = 0;
	tmp->width_asterisk = -1;
	tmp->width = 0;
	tmp->precision_ast = -1;
	tmp->precision = 0;
	tmp->next = NULL;
	return (tmp);
}

static int		look_up(char *format, t_printf *cur, t_args **args)
{
	int			max_arg;

	max_arg = MAX_PRINTF_ARG;
	while (--max_arg)
		args[max_arg] = NULL;
	while (*format)
		if (*format == '%')
		{
			if (*(format + 1))
				if (ft_printf_pars(&format, cur, args, 0) == -1)
					return (-1);
			if (*(++format))
			{
				cur->next = new_node(format);
				cur->next->arg_number = cur->arg_number + 1;
			}
			cur = cur->next;
		}
		else
		{
			cur->text_length++;
			format++;
		}
	return (0);
}

int				ft_printf(const char *format, ...)
{
	va_list		ap;
	t_printf	*head;
	t_args		*args[MAX_PRINTF_ARG];
	int			res;

	head = new_node((char*)format);
	head->arg_number = 1;
	if (look_up((char*)format, head, args) == -1)
	{
		free_printf(head);
		return (-1);
	}
	va_start(ap, format);
	if (ft_printf_get_args(args, ap, 0) == -1)
	{
		free_all(args);
		free_printf(head);
		va_end(ap);
		return (-1);
	}
	va_end(ap);
	if ((res = ft_printf_print(head)) == -1)
		return (-1);
	return (res);
}
